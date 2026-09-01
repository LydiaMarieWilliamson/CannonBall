#pragma once

#include "Types.hpp"

class RomLoader;

class hwtiles {
public:
   enum {
      LEFT,
      RIGHT,
      CENTRE,
   };
   Num1 text_ram[0x1000]; // Text RAM
   Num1 tile_ram[0x10000]; // Tile RAM
   hwtiles(void);
   ~hwtiles(void);
   void init(Num1 *src_tiles, const bool hires);
   void patch_tiles(RomLoader *patch);
   void restore_tiles();
   void set_x_clamp(const Num2);
   void update_tile_values();
   void render_tile_layer(Num2 *, Num1, Num1);
   void render_text_layer(Num2 *, Num1);
   void render_all_tiles(Num2 *);
private:
   Int2 x_clamp;
// S16 Width, ignoring widescreen related scaling.
   Num2 s16_width_noscale;
   static const int TILES_LENGTH = 0x10000;
   Num4 tiles[TILES_LENGTH]; // Converted tiles
   Num4 tiles_backup[TILES_LENGTH]; // Converted tiles (backup without patch)
   Num2 page[4];
   Num2 scroll_x[4];
   Num2 scroll_y[4];
   Num1 tile_banks[2];
   static const Num2 NUM_TILES = 0x2000; // Length of graphic rom/24
   static const Num2 TILEMAP_COLOUR_OFFSET = 0x1c00;
   void (hwtiles::*render8x8_tile_mask)(Num2 *buf, Num2 nTileNumber, Num2 StartX, Num2 StartY, Num2 nTilePalette, Num2 nColourDepth, Num2 nMaskColour, Num2 nPaletteOffset);
   void (hwtiles::*render8x8_tile_mask_clip)(Num2 *buf, Num2 nTileNumber, Int2 StartX, Int2 StartY, Num2 nTilePalette, Num2 nColourDepth, Num2 nMaskColour, Num2 nPaletteOffset);
   void render8x8_tile_mask_lores(Num2 *buf, Num2 nTileNumber, Num2 StartX, Num2 StartY, Num2 nTilePalette, Num2 nColourDepth, Num2 nMaskColour, Num2 nPaletteOffset);
   void render8x8_tile_mask_clip_lores(Num2 *buf, Num2 nTileNumber, Int2 StartX, Int2 StartY, Num2 nTilePalette, Num2 nColourDepth, Num2 nMaskColour, Num2 nPaletteOffset);
   void render8x8_tile_mask_hires(Num2 *buf, Num2 nTileNumber, Num2 StartX, Num2 StartY, Num2 nTilePalette, Num2 nColourDepth, Num2 nMaskColour, Num2 nPaletteOffset);
   void render8x8_tile_mask_clip_hires(Num2 *buf, Num2 nTileNumber, Int2 StartX, Int2 StartY, Num2 nTilePalette, Num2 nColourDepth, Num2 nMaskColour, Num2 nPaletteOffset);
   inline void set_pixel_x4(Num2 *buf, Num4 data);
};
