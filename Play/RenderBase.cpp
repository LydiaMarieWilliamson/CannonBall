#include "RenderBase.hpp"
#include <iostream>
#include <cmath>

RenderBase::RenderBase() {
   surface = NULL;
   screen_pixels = NULL;
   orig_width = 0;
   orig_height = 0;
}

// Setup screen size
bool RenderBase::sdl_screen_size() {
   if (orig_width == 0 || orig_height == 0) {
      SDL_DisplayMode info;
      SDL_GetCurrentDisplayMode(0, &info);
      orig_width = info.w;
      orig_height = info.h;
   }
   scn_width = orig_width;
   scn_height = orig_height;
   return true;
}

// See: SDL_PixelFormat
#define CURRENT_RGB() (r << Rshift) | (g << Gshift) | (b << Bshift);

void RenderBase::convert_palette(Num4 adr, Num4 r1, Num4 g1, Num4 b1) {
   adr >>= 1;
   Num4 r = r1*8;
   Num4 g = g1*8;
   Num4 b = b1*8;
   rgb[adr] = CURRENT_RGB();
// Create shadow colours at end of RGB array
   r = r1*shadow_multi/31;
   g = g1*shadow_multi/31;
   b = b1*shadow_multi/31;
   rgb[adr + S16_PALETTE_ENTRIES] = CURRENT_RGB(); // Add to the end of the array
// Highlight colour code would be added here, but unused.
}

void RenderBase::set_shadow_intensity(float f) {
   shadow_multi = (int)std::round(255.0f*f);
}
