#include "Video.hpp"
#include "Video/Sprites.hpp"
#include "Globals.hpp"
#include "Arena/Config.hpp"

// Video Emulation: OutRun Sprite Rendering Hardware.
// Based on MAME source code.
//
// Copyright Aaron Giles.
// All rights reserved.

// Out Run/X-Board-style sprites
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	Offs	Bits			Usage
//	+0	e――――――― ――――――――	Signify end of sprite list
//	+0	―h―h―――― ――――――――	Hide this sprite if either bit is set
//	+0	――――bbb― ――――――――	Sprite bank
//	+0	―――――――t tttttttt	Top scanline of sprite + 256
//	+2	oooooooo oooooooo	Offset within selected sprite bank
//	+4	ppppppp― ――――――――	Signed 7-bit pitch value between scanlines
//	+4	―――――――x xxxxxxxx	X position of sprite (position $BE is screen position 0)
//	+6	―s―――――― ――――――――	Enable shadows
//	+6	――pp―――― ――――――――	Sprite priority, relative to tilemaps
//	+6	――――――vv vvvvvvvv	Vertical zoom factor (0x200 = full size, 0x100 = half size, 0x300 = 2x size)
//	+8	y――――――― ――――――――	Render from top-to-bottom (1) or bottom-to-top (0) on screen
//	+8	―f―――――― ――――――――	Horizontal flip: read the data backwards if set
//	+8	――x――――― ――――――――	Render from left-to-right (1) or right-to-left (0) on screen
//	+8	――――――hh hhhhhhhh	Horizontal zoom factor (0x200 = full size, 0x100 = half size, 0x300 = 2x size)
//	+E	dddddddd dddddddd	Scratch space for current address
// Out Run only:
//	+A	hhhhhhhh ――――――――	Height in scanlines - 1
//	+A	―――――――― ―ccccccc	Sprite color palette
// X-Board only:
//	+A	――――hhhh hhhhhhhh	Height in scanlines - 1
//	+C	―――――――― cccccccc	Sprite color palette
// Final bitmap format:
//		―s―――――― ――――――――	Shadow control
//		――pp―――― ――――――――	Sprite priority
//		――――cccc cccc――――	Sprite color palette
//		―――――――― ――――llll	4-bit pixel data

// Enable for hardware pixel accuracy, where sprite shadowing delayed by 1 clock cycle (slower)
#define PIXEL_ACCURACY 0

hwsprites::hwsprites() {
}

hwsprites::~hwsprites() {
}

void hwsprites::init(const Num1 *src_sprites) {
   reset();
   if (src_sprites) {
   // Convert S16 tiles to a more useable format
      const Num1 *spr = src_sprites;
      for (Num4 i = 0; i < SPRITES_LENGTH; i++) {
         Num1 d3 = *spr++;
         Num1 d2 = *spr++;
         Num1 d1 = *spr++;
         Num1 d0 = *spr++;
         sprites[i] = (d0 << 24) | (d1 << 16) | (d2 << 8) | d3;
      }
   }
}

void hwsprites::reset() {
// Clear Sprite RAM buffers
   for (Num2 i = 0; i < SPRITE_RAM_SIZE; i++) {
      ram[i] = 0;
      ramBuff[i] = 0;
   }
}

// Clip areas of the screen in wide-screen mode
void hwsprites::set_x_clip(bool on) {
// Clip to central 320 width window.
   if (on) {
      x1 = config.s16_x_off;
      x2 = x1 + S16_WIDTH;
      if (config.video.hires) {
         x1 <<= 1;
         x2 <<= 1;
      }
   }
// Allow full wide-screen.
   else {
      x1 = 0;
      x2 = config.s16_width;
   }
}

Num1 hwsprites::read(const Num2 adr) {
   Num2 a = adr >> 1;
   if ((adr&1) == 1)
      return ram[a]&0xff;
   else
      return ram[a] >> 8;
}

void hwsprites::write(const Num2 adr, const Num2 data) {
   ram[adr >> 1] = data;
}

// Copy back buffer to main ram, ready for blit
void hwsprites::swap() {
   Num2 *src = (Num2 *)ram;
   Num2 *dst = (Num2 *)ramBuff;
// swap the halves of the road RAM
   for (Num2 i = 0; i < SPRITE_RAM_SIZE; i++) {
      Num2 temp = *src;
      *src++ = *dst;
      *dst++ = temp;
   }
}

#if PIXEL_ACCURACY
// Reproduces glowy edge around sprites on top of shadows as seen on Hardware.
// Believed to be caused by shadowing being out by one clock cycle / pixel.
//
// 1/	Sprites Drawn on top of Shadow clears the shadow flags for its opaque pixels.
// 2/	Either the flag clear or the sprite itself is offset by one pixel horizontally.
//
// Thanks to Alex B. for this implementation.
#   define draw_pixel() { \
   if (x >= x1 && x < x2) { \
      if (shadow && pix == 0xa) { \
         pPixel[x] &= 0xfff; \
         pPixel[x] += S16_PALETTE_ENTRIES; \
      } else if (pix != 0 && pix != 15) { \
         if (x > x1) pPixel[x-1] &= 0xfff; \
         pPixel[x] = (pix | color); \
      } \
   } \
}
#else
#   define draw_pixel() { \
   if (x >= x1 && x < x2 && pix != 0 && pix != 15) { \
      if (shadow && pix == 0xa) { \
         pPixel[x] &= 0xfff; \
         pPixel[x] += S16_PALETTE_ENTRIES; \
      } else { \
         pPixel[x] = (pix | color); \
      } \
   } \
}
#endif

void hwsprites::render(const Num1 priority) {
   const Num4 numbanks = SPRITES_LENGTH/0x10000;
   for (Num2 data = 0; data < SPRITE_RAM_SIZE; data += 8) {
   // stop when we hit the end of sprite list
      if ((ramBuff[data + 0]&0x8000) != 0) break;
      Num4 sprpri = 1 << ((ramBuff[data + 3] >> 12)&3);
      if (sprpri != priority) continue;
   // if hidden, or top greater than/equal to bottom, or invalid bank, punt
      Int2 hide = (ramBuff[data + 0]&0x5000);
      Int4 height = (ramBuff[data + 5] >> 8) + 1;
      if (hide != 0 || height == 0) continue;
      Int2 bank = (ramBuff[data + 0] >> 9)&7;
      Int4 top = (ramBuff[data + 0]&0x1ff) - 0x100;
      Num4 addr = ramBuff[data + 1];
      Int4 pitch = ((ramBuff[data + 2] >> 1) | ((ramBuff[data + 4]&0x1000) << 3)) >> 8;
      Int4 xpos = ramBuff[data + 6]; // moved from original structure to accomodate widescreen
      Num1 shadow = (ramBuff[data + 3] >> 14)&1;
      Int4 vzoom = ramBuff[data + 3]&0x7ff;
      Int4 ydelta = ((ramBuff[data + 4]&0x8000) != 0)? 1: -1;
      Int4 flip = (~ramBuff[data + 4] >> 14)&1;
      Int4 xdelta = ((ramBuff[data + 4]&0x2000) != 0)? 1: -1;
      Int4 hzoom = ramBuff[data + 4]&0x7ff;
      Int4 color = COLOR_BASE + ((ramBuff[data + 5]&0x7f) << 4);
      Int4 x, y, ytarget, yacc = 0, pix;
   // adjust X coordinate
   // note: the threshhold below is a guess. If it is too high, rachero will draw garbage
   // If it is too low, smgp won't draw the bottom part of the road
      if (xpos < 0x80 && xdelta < 0)
         xpos += 0x200;
      xpos -= 0xbe;
   // initialize the end address to the start address
      ramBuff[data + 7] = addr;
   // clamp to within the memory region size
      if (numbanks)
         bank %= numbanks;
      const Num4 *spritedata = sprites + 0x10000*bank;
   // clamp to a maximum of 8x (not 100% confirmed)
      if (vzoom < 0x40) vzoom = 0x40;
      if (hzoom < 0x40) hzoom = 0x40;
   // loop from top to bottom
      ytarget = top + ydelta*height;
   // Adjust for widescreen mode
      xpos += config.s16_x_off;
   // Adjust for hi-res mode
      if (config.video.hires) {
         xpos <<= 1;
         top <<= 1;
         ytarget <<= 1;
         hzoom >>= 1;
         vzoom >>= 1;
      }
      for (y = top; y != ytarget; y += ydelta) {
      // skip drawing if not within the cliprect
         if (y >= 0 && y < config.s16_height) {
            Num2 *pPixel = &video.pixels[y*config.s16_width];
            Int4 xacc = 0;
         // non-flipped case
            if (flip == 0) {
            // start at the word before because we preincrement below
               ramBuff[data + 7] = (addr - 1);
               for (x = xpos; (xdelta > 0 && x < config.s16_width) || (xdelta < 0 && x >= 0); ) {
                  Num4 pixels = spritedata[++ramBuff[data + 7]]; // Add to base sprite data the vzoom value
               // draw four pixels
                  pix = (pixels >> 28)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 24)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 20)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 16)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 12)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 8)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 4)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 0)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
               // stop if the second-to-last pixel in the group was 0xf
                  if ((pixels&0x000000f0) == 0x000000f0)
                     break;
               }
            }
         // flipped case
            else {
            // start at the word after because we predecrement below
               ramBuff[data + 7] = (addr + 1);
               for (x = xpos; (xdelta > 0 && x < config.s16_width) || (xdelta < 0 && x >= 0); ) {
                  Num4 pixels = spritedata[--ramBuff[data + 7]];
               // draw four pixels
                  pix = (pixels >> 0)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 4)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 8)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 12)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 16)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 20)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 24)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
                  pix = (pixels >> 28)&0xf;
                  while (xacc < 0x200) {
                     draw_pixel();
                     x += xdelta;
                     xacc += hzoom;
                  }
                  xacc -= 0x200;
               // stop if the second-to-last pixel in the group was 0xf
                  if ((pixels&0x0f000000) == 0x0f000000)
                     break;
               }
            }
         }
      // accumulate zoom factors; if we carry into the high bit, skip an extra row
         yacc += vzoom;
         addr += pitch*(yacc >> 9);
         yacc &= 0x1ff;
      }
   }
}
