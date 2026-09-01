#include <cstring> // memcpy
#include "Globals.hpp"
#include "LoadROM.hpp"
#include "Video/Tiles.hpp"
#include "Arena/Config.hpp"

// Video Emulation: OutRun Tilemap Hardware.
// Based on MAME source code.
//
// Copyright Aaron Giles.
// All rights reserved.

// System 16B-style tilemaps
// ━━━━━━━━━━━━━━━━━━━━━━━━━
// 16 total pages
// Column/rowscroll enabled via bits in text layer
// Alternate tilemap support
//
// Tile format:
//	Bits			Usage
//	p――――――― ――――――――	Tile priority versus sprites
//	―??――――― ――――――――	Unknown
//	―――ccccc cc――――――	Tile color palette
//	―――nnnnn nnnnnnnn	Tile index
// Text format:
//	Bits			Usage
//	p――――――― ――――――――	Tile priority versus sprites
//	―???―――― ――――――――	Unknown
//	――――ccc― ――――――――	Tile color palette
//	―――――――n nnnnnnnn	Tile index
// Alternate tile format:
//	Bits			Usage
//	p――――――― ――――――――	Tile priority versus sprites
//	―??――――― ――――――――	Unknown
//	――――cccc ccc―――――	Tile color palette
//	―――nnnnn nnnnnnnn	Tile index
// Alternate text format:
//	Bits			Usage
//	p――――――― ――――――――	Tile priority versus sprites
//	―???―――― ――――――――	Unknown
//	―――――ccc ――――――――	Tile color palette
//	―――――――― nnnnnnnn	Tile index
// Text RAM:
//	Offset	Bits			Usage
//	E80	aaaabbbb ccccdddd	Foreground tilemap page select
//	E82	aaaabbbb ccccdddd	Background tilemap page select
//	E84	aaaabbbb ccccdddd	Alternate foreground tilemap page select
//	E86	aaaabbbb ccccdddd	Alternate background tilemap page select
//	E90	c――――――― ――――――――	Foreground tilemap column scroll enable
//		―――――――v vvvvvvvv	Foreground tilemap vertical scroll
//	E92	c――――――― ――――――――	Background tilemap column scroll enable
//		―――――――v vvvvvvvv	Background tilemap vertical scroll
//	E94	―――――――v vvvvvvvv	Alternate foreground tilemap vertical scroll
//	E96	―――――――v vvvvvvvv	Alternate background tilemap vertical scroll
//	E98	r――――――― ――――――――	Foreground tilemap row scroll enable
//		――――――hh hhhhhhhh	Foreground tilemap horizontal scroll
//	E9A	r――――――― ――――――――	Background tilemap row scroll enable
//		――――――hh hhhhhhhh	Background tilemap horizontal scroll
//	E9C	――――――hh hhhhhhhh	Alternate foreground tilemap horizontal scroll
//	E9E	――――――hh hhhhhhhh	Alternate background tilemap horizontal scroll
//	F16-F3F	―――――――― vvvvvvvv	Foreground tilemap per-16-pixel-column vertical scroll
//	F56-F7F	―――――――― vvvvvvvv	Background tilemap per-16-pixel-column vertical scroll
//	F80-FB7	a――――――― ――――――――	Foreground tilemap per-8-pixel-row alternate tilemap enable
//		―――――――h hhhhhhhh	Foreground tilemap per-8-pixel-row horizontal scroll
//	FC0-FF7	a――――――― ――――――――	Background tilemap per-8-pixel-row alternate tilemap enable
//		―――――――h hhhhhhhh	Background tilemap per-8-pixel-row horizontal scroll

hwtiles::hwtiles(void) {
   for (int i = 0; i < 2; i++)
      tile_banks[i] = i;
   set_x_clamp(CENTRE);
}

hwtiles::~hwtiles(void) {
}

// Convert S16 tiles to a more useable format
void hwtiles::init(Num1 *src_tiles, const bool hires) {
   if (src_tiles) {
      for (int i = 0; i < TILES_LENGTH; i++) {
         Num1 p0 = src_tiles[i];
         Num1 p1 = src_tiles[i + 0x10000];
         Num1 p2 = src_tiles[i + 0x20000];
         Num4 val = 0;
         for (int ii = 0; ii < 8; ii++) {
            Num1 bit = 7 - ii;
            Num1 pix = ((((p0 >> bit))&1) | (((p1 >> bit) << 1)&2) | (((p2 >> bit) << 2)&4));
            val = (val << 4) | pix;
         }
         tiles[i] = val; // Store converted value
      }
      memcpy(tiles_backup, tiles, TILES_LENGTH*sizeof(Num4));
   }
   if (hires) {
      s16_width_noscale = config.s16_width >> 1;
      render8x8_tile_mask = &hwtiles::render8x8_tile_mask_hires;
      render8x8_tile_mask_clip = &hwtiles::render8x8_tile_mask_clip_hires;
   } else {
      s16_width_noscale = config.s16_width;
      render8x8_tile_mask = &hwtiles::render8x8_tile_mask_lores;
      render8x8_tile_mask_clip = &hwtiles::render8x8_tile_mask_clip_lores;
   }
}

// Patch Tileset with new data
void hwtiles::patch_tiles(RomLoader *patch) {
   memcpy(tiles_backup, tiles, TILES_LENGTH*sizeof(Num4));
   for (Num4 i = 0; i < patch->length; ) {
      Num4 tile_index = patch->read16(&i) << 3;
      tiles[tile_index++] = patch->read32(&i);
      tiles[tile_index++] = patch->read32(&i);
      tiles[tile_index++] = patch->read32(&i);
      tiles[tile_index++] = patch->read32(&i);
      tiles[tile_index++] = patch->read32(&i);
      tiles[tile_index++] = patch->read32(&i);
      tiles[tile_index++] = patch->read32(&i);
      tiles[tile_index++] = patch->read32(&i);
   }
}

void hwtiles::restore_tiles() {
   memcpy(tiles, tiles_backup, TILES_LENGTH*sizeof(Num4));
}

// Set Tilemap X Clamp
//
// This is used for the widescreen mode, in order to clamp the tilemap to a location of the screen.
//
// In-Game we must clamp right to avoid page scrolling issues.
//
// The clamp will always be 192 for the non-widescreen mode.
void hwtiles::set_x_clamp(const Num2 props) {
   if (props == LEFT) {
      x_clamp = 192;
   } else if (props == RIGHT) {
      x_clamp = (512 - s16_width_noscale);
   } else if (props == CENTRE) {
      x_clamp = 192 - config.s16_x_off;
   }
}

void hwtiles::update_tile_values() {
   for (int i = 0; i < 4; i++) {
      page[i] = ((text_ram[0xe80 + (i*2) + 0] << 8) | text_ram[0xe80 + (i*2) + 1]);
      scroll_x[i] = ((text_ram[0xe98 + (i*2) + 0] << 8) | text_ram[0xe98 + (i*2) + 1]);
      scroll_y[i] = ((text_ram[0xe90 + (i*2) + 0] << 8) | text_ram[0xe90 + (i*2) + 1]);
   }
}

// A quick and dirty debug function to display the contents of tile memory.
void hwtiles::render_all_tiles(Num2 *buf) {
   Num4 Code = 0, Colour = 5, x, y;
   for (y = 0; y < 224; y += 8) {
      for (x = 0; x < 320; x += 8) {
         (this->*render8x8_tile_mask)(buf, Code, x, y, Colour, 3, 0, TILEMAP_COLOUR_OFFSET);
         Code++;
      }
   }
}

void hwtiles::render_tile_layer(Num2 *buf, Num1 page_index, Num1 priority_draw) {
   Int2 Colour, x, y, Priority = 0;
   Num2 ActPage = 0;
   Num2 EffPage = page[page_index];
   Num2 xScroll = scroll_x[page_index];
   Num2 yScroll = scroll_y[page_index];
// Need to support this at each row/column
   if ((xScroll&0x8000) != 0)
      xScroll = (text_ram[0xf80 + (0x40*page_index) + 0] << 8) | text_ram[0xf80 + (0x40*page_index) + 1];
   if ((yScroll&0x8000) != 0)
      yScroll = (text_ram[0xf16 + (0x40*page_index) + 0] << 8) | text_ram[0xf16 + (0x40*page_index) + 1];
   for (int my = 0; my < 64; my++) {
      for (int mx = 0; mx < 128; mx++) {
         if (my < 32 && mx < 64) // top left
            ActPage = (EffPage >> 0)&0x0f;
         if (my < 32 && mx >= 64) // top right
            ActPage = (EffPage >> 4)&0x0f;
         if (my >= 32 && mx < 64) // bottom left
            ActPage = (EffPage >> 8)&0x0f;
         if (my >= 32 && mx >= 64) // bottom right page
            ActPage = (EffPage >> 12)&0x0f;
         Num4 TileIndex = 64*32*2*ActPage + ((2*64*my)&0xfff) + ((2*mx)&0x7f);
         Num2 Data = (tile_ram[TileIndex + 0] << 8) | tile_ram[TileIndex + 1];
         Priority = (Data >> 15)&1;
         if (Priority == priority_draw) {
            Num4 Code = Data&0x1fff;
            Code = tile_banks[Code/0x1000]*0x1000 + Code%0x1000;
            Code &= (NUM_TILES - 1);
            if (Code == 0) continue;
            Colour = (Data >> 6)&0x7f;
            x = 8*mx;
            y = 8*my;
         // We take into account the internal screen resolution here
         // to account for widescreen mode.
            x -= (x_clamp - xScroll)&0x3ff;
            if (x < -x_clamp)
               x += 1024;
            y -= yScroll&0x1ff;
            if (y < -288)
               y += 512;
            Num2 ColourOff = TILEMAP_COLOUR_OFFSET;
            if (Colour >= 0x20)
               ColourOff = 0x100 | TILEMAP_COLOUR_OFFSET;
            if (Colour >= 0x40)
               ColourOff = 0x200 | TILEMAP_COLOUR_OFFSET;
            if (Colour >= 0x60)
               ColourOff = 0x300 | TILEMAP_COLOUR_OFFSET;
            if (x > 7 && x < (s16_width_noscale - 8) && y > 7 && y <= (S16_HEIGHT - 8))
               (this->*render8x8_tile_mask)(buf, Code, x, y, Colour, 3, 0, ColourOff);
            else if (x > -8 && x < s16_width_noscale && y > -8 && y < S16_HEIGHT)
               (this->*render8x8_tile_mask_clip)(buf, Code, x, y, Colour, 3, 0, ColourOff);
         }
      }
   }
}

void hwtiles::render_text_layer(Num2 *buf, Num1 priority_draw) {
   Num2 mx, my, Code, Colour, x, y, Priority, TileIndex = 0;
   for (my = 0; my < 32; my++) {
      for (mx = 0; mx < 64; mx++) {
         Code = (text_ram[TileIndex + 0] << 8) | text_ram[TileIndex + 1];
         Priority = (Code >> 15)&1;
         if (Priority == priority_draw) {
            Colour = (Code >> 9)&0x07;
            Code &= 0x1ff;
            Code += tile_banks[0]*0x1000;
            Code &= (NUM_TILES - 1);
            if (Code != 0) {
               x = 8*mx;
               y = 8*my;
               x -= 192;
            // We also adjust the text layer for wide-screen below.
            // But don't allow painting in the wide-screen areas to avoid graphical glitches.
               if (x > 7 && x < (s16_width_noscale - 8) && y > 7 && y <= (S16_HEIGHT - 8))
                  (this->*render8x8_tile_mask)(buf, Code, x + config.s16_x_off, y, Colour, 3, 0, TILEMAP_COLOUR_OFFSET);
               else if (x > -8 && x < s16_width_noscale && y >= 0 && y < S16_HEIGHT)
                  (this->*render8x8_tile_mask_clip)(buf, Code, x + config.s16_x_off, y, Colour, 3, 0, TILEMAP_COLOUR_OFFSET);
            }
         }
         TileIndex += 2;
      }
   }
}

void hwtiles::render8x8_tile_mask_lores(Num2 *buf, Num2 nTileNumber, Num2 StartX, Num2 StartY, Num2 nTilePalette, Num2 nColourDepth, Num2 nMaskColour, Num2 nPaletteOffset) {
   Num4 nPalette = (nTilePalette << nColourDepth) | nMaskColour;
   Num4 *pTileData = tiles + (nTileNumber << 3);
   buf += (StartY*config.s16_width) + StartX;
   for (int y = 0; y < 8; y++) {
      Num4 p0 = *pTileData;
      if (p0 != nMaskColour) {
         Num4 c7 = p0&0xf;
         Num4 c6 = (p0 >> 4)&0xf;
         Num4 c5 = (p0 >> 8)&0xf;
         Num4 c4 = (p0 >> 12)&0xf;
         Num4 c3 = (p0 >> 16)&0xf;
         Num4 c2 = (p0 >> 20)&0xf;
         Num4 c1 = (p0 >> 24)&0xf;
         Num4 c0 = (p0 >> 28);
         if (c0) buf[0] = nPalette + c0;
         if (c1) buf[1] = nPalette + c1;
         if (c2) buf[2] = nPalette + c2;
         if (c3) buf[3] = nPalette + c3;
         if (c4) buf[4] = nPalette + c4;
         if (c5) buf[5] = nPalette + c5;
         if (c6) buf[6] = nPalette + c6;
         if (c7) buf[7] = nPalette + c7;
      }
      buf += config.s16_width;
      pTileData++;
   }
}

void hwtiles::render8x8_tile_mask_clip_lores(Num2 *buf, Num2 nTileNumber, Int2 StartX, Int2 StartY, Num2 nTilePalette, Num2 nColourDepth, Num2 nMaskColour, Num2 nPaletteOffset) {
   Num4 nPalette = (nTilePalette << nColourDepth) | nMaskColour;
   Num4 *pTileData = tiles + (nTileNumber << 3);
   buf += (StartY*config.s16_width) + StartX;
   for (int y = 0; y < 8; y++) {
      if ((StartY + y) >= 0 && (StartY + y) < S16_HEIGHT) {
         Num4 p0 = *pTileData;
         if (p0 != nMaskColour) {
            Num4 c7 = p0&0xf;
            Num4 c6 = (p0 >> 4)&0xf;
            Num4 c5 = (p0 >> 8)&0xf;
            Num4 c4 = (p0 >> 12)&0xf;
            Num4 c3 = (p0 >> 16)&0xf;
            Num4 c2 = (p0 >> 20)&0xf;
            Num4 c1 = (p0 >> 24)&0xf;
            Num4 c0 = (p0 >> 28);
            if (c0 && 0 + StartX >= 0 && 0 + StartX < config.s16_width) buf[0] = nPalette + c0;
            if (c1 && 1 + StartX >= 0 && 1 + StartX < config.s16_width) buf[1] = nPalette + c1;
            if (c2 && 2 + StartX >= 0 && 2 + StartX < config.s16_width) buf[2] = nPalette + c2;
            if (c3 && 3 + StartX >= 0 && 3 + StartX < config.s16_width) buf[3] = nPalette + c3;
            if (c4 && 4 + StartX >= 0 && 4 + StartX < config.s16_width) buf[4] = nPalette + c4;
            if (c5 && 5 + StartX >= 0 && 5 + StartX < config.s16_width) buf[5] = nPalette + c5;
            if (c6 && 6 + StartX >= 0 && 6 + StartX < config.s16_width) buf[6] = nPalette + c6;
            if (c7 && 7 + StartX >= 0 && 7 + StartX < config.s16_width) buf[7] = nPalette + c7;
         }
      }
      buf += config.s16_width;
      pTileData++;
   }
}

// Additional routines for Hi-Res Mode.
// ────────────────────────────────────
// Note that the tilemaps are displayed at the same resolution, we just want everything to be proportional.
void hwtiles::render8x8_tile_mask_hires(Num2 *buf, Num2 nTileNumber, Num2 StartX, Num2 StartY, Num2 nTilePalette, Num2 nColourDepth, Num2 nMaskColour, Num2 nPaletteOffset) {
   Num4 nPalette = (nTilePalette << nColourDepth) | nMaskColour;
   Num4 *pTileData = tiles + (nTileNumber << 3);
   buf += ((StartY << 1)*config.s16_width) + (StartX << 1);
   for (int y = 0; y < 8; y++) {
      Num4 p0 = *pTileData;
      if (p0 != nMaskColour) {
         Num4 c7 = p0&0xf;
         Num4 c6 = (p0 >> 4)&0xf;
         Num4 c5 = (p0 >> 8)&0xf;
         Num4 c4 = (p0 >> 12)&0xf;
         Num4 c3 = (p0 >> 16)&0xf;
         Num4 c2 = (p0 >> 20)&0xf;
         Num4 c1 = (p0 >> 24)&0xf;
         Num4 c0 = (p0 >> 28);
         if (c0) set_pixel_x4(&buf[0], nPalette + c0);
         if (c1) set_pixel_x4(&buf[2], nPalette + c1);
         if (c2) set_pixel_x4(&buf[4], nPalette + c2);
         if (c3) set_pixel_x4(&buf[6], nPalette + c3);
         if (c4) set_pixel_x4(&buf[8], nPalette + c4);
         if (c5) set_pixel_x4(&buf[10], nPalette + c5);
         if (c6) set_pixel_x4(&buf[12], nPalette + c6);
         if (c7) set_pixel_x4(&buf[14], nPalette + c7);
      }
      buf += (config.s16_width << 1);
      pTileData++;
   }
}

void hwtiles::render8x8_tile_mask_clip_hires(Num2 *buf, Num2 nTileNumber, Int2 StartX, Int2 StartY, Num2 nTilePalette, Num2 nColourDepth, Num2 nMaskColour, Num2 nPaletteOffset) {
   Num4 nPalette = (nTilePalette << nColourDepth) | nMaskColour;
   Num4 *pTileData = tiles + (nTileNumber << 3);
   buf += ((StartY << 1)*config.s16_width) + (StartX << 1);
   for (int y = 0; y < 8; y++) {
      if ((StartY + y) >= 0 && (StartY + y) < S16_HEIGHT) {
         Num4 p0 = *pTileData;
         if (p0 != nMaskColour) {
            Num4 c7 = p0&0xf;
            Num4 c6 = (p0 >> 4)&0xf;
            Num4 c5 = (p0 >> 8)&0xf;
            Num4 c4 = (p0 >> 12)&0xf;
            Num4 c3 = (p0 >> 16)&0xf;
            Num4 c2 = (p0 >> 20)&0xf;
            Num4 c1 = (p0 >> 24)&0xf;
            Num4 c0 = (p0 >> 28);
            if (c0 && 0 + StartX >= 0 && 0 + StartX < s16_width_noscale) set_pixel_x4(&buf[0], nPalette + c0);
            if (c1 && 1 + StartX >= 0 && 1 + StartX < s16_width_noscale) set_pixel_x4(&buf[2], nPalette + c1);
            if (c2 && 2 + StartX >= 0 && 2 + StartX < s16_width_noscale) set_pixel_x4(&buf[4], nPalette + c2);
            if (c3 && 3 + StartX >= 0 && 3 + StartX < s16_width_noscale) set_pixel_x4(&buf[6], nPalette + c3);
            if (c4 && 4 + StartX >= 0 && 4 + StartX < s16_width_noscale) set_pixel_x4(&buf[8], nPalette + c4);
            if (c5 && 5 + StartX >= 0 && 5 + StartX < s16_width_noscale) set_pixel_x4(&buf[10], nPalette + c5);
            if (c6 && 6 + StartX >= 0 && 6 + StartX < s16_width_noscale) set_pixel_x4(&buf[12], nPalette + c6);
            if (c7 && 7 + StartX >= 0 && 7 + StartX < s16_width_noscale) set_pixel_x4(&buf[14], nPalette + c7);
         }
      }
      buf += (config.s16_width << 1);
      pTileData++;
   }
}

// Hires Mode: Set 4 pixels instead of one.
void hwtiles::set_pixel_x4(Num2 *buf, Num4 data) {
   buf[0] = buf[1] = buf[0 + config.s16_width] = buf[1 + config.s16_width] = data;
}
