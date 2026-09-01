#pragma once

#include "../Types.hpp"
#include "../Globals.hpp"
#include <SDL.h>

// Abstract Rendering Class
class RenderBase {
public:
   RenderBase();
   virtual bool init(int src_width, int src_height, int scale, int video_mode, int scanlines) = 0;
   virtual void disable() = 0;
   virtual bool start_frame() = 0;
   virtual bool finalize_frame() = 0;
   virtual void draw_frame(Num2 *pixels) = 0;
   void convert_palette(Num4 adr, Num4 r1, Num4 g1, Num4 b1);
   void set_shadow_intensity(float f);
   virtual bool supports_window() {
      return true;
   }
   virtual bool supports_vsync() {
      return false;
   }
protected:
   SDL_Surface *surface;
// SDL2 window
   SDL_Window *window;
// Palette Lookup
   Num4 rgb[S16_PALETTE_ENTRIES*2]; // Extended to hold shadow colours
   Num4 *screen_pixels;
// Original Screen Width & Height
   Num2 orig_width, orig_height;
// Screen setup properties.
// ────────────────────────
// Example below:
//	┌──┬────────────────┬──┐
//	│  │                │  │ <─────	screen size		(e.g. 1280 × 720)
//	│  │                │  │
//	│  │                │<─┼───────	destination size	(e.g. 1027 × 720) to maintain aspect ratio
//	│  │                │  │
//	│  │                │  │	source size		(e.g. 320  × 224) System 16 proportions
//	└──┴────────────────┴──┘
// Source texture / pixel array that we are going to manipulate
   int src_width, src_height;
// Destination window width and height
   int dst_width, dst_height;
// Screen width and height
   int scn_width, scn_height;
// Full-Screen, Stretch, Window
   int video_mode;
// Scanline density. 0 = Off, 1 = Full
   int scanlines;
// Screen Scale
   int scale;
// Offsets (for full-screen mode, where x/y resolution isn't a multiple of the original height)
   Num4 screen_xoff, screen_yoff;
// SDL Pixel Format Codes. These differ between platforms.
   Num1 Rshift, Gshift, Bshift;
   Num4 Rmask, Gmask, Bmask;
// Shadow intensity multiplier
   int shadow_multi;
   bool sdl_screen_size();
};
