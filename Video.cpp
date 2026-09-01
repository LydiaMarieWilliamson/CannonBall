// Video Rendering.
// -	Renders the System 16 Video Layers
// -	Handles Reads and Writes to these layers from the main game code
// -	Interfaces with platform specific rendering code
//
// Copyright Chris White.
// See License.txt for more details.
#include <iostream>
#include "Video.hpp"
#include "Globals.hpp"
#include "Arena/Config.hpp"
#include "Game/Road.hpp"
#ifdef WITH_OPENGL
#   include "Play/RenderGL.hpp"
#elif WITH_OPENGLES
#   include "Play/RenderGLES.hpp"
#else
#   include "Play/RenderSurface.hpp"
#endif

Video video;

Video::Video(void) {
   renderer = new Render();
   pixels = NULL;
   sprite_layer = new hwsprites();
   tile_layer = new hwtiles();
   set_shadow_intensity(shadow::ORIGINAL);
   enabled = false;
}

Video::~Video(void) {
   delete sprite_layer;
   delete tile_layer;
   if (pixels) delete[]pixels;
   renderer->disable();
   delete renderer;
}

int Video::init(Roms *roms, video_settings_t *settings) {
   if (!set_video_mode(settings))
      return 0;
// Internal pixel array. The size of this is always constant
   if (pixels) delete[]pixels;
   pixels = new Num2[config.s16_width*config.s16_height];
// Convert S16 tiles to a more useable format
   tile_layer->init(roms->tiles.rom, config.video.hires != 0);
   clear_tile_ram();
   clear_text_ram();
   if (roms->tiles.rom) {
      delete[]roms->tiles.rom;
      roms->tiles.rom = NULL;
   }
// Convert S16 sprites
   sprite_layer->init(roms->sprites.rom);
   if (roms->sprites.rom) {
      delete[]roms->sprites.rom;
      roms->sprites.rom = NULL;
   }
// Convert S16 Road Stuff
   hwroad.init(roms->road.rom, config.video.hires != 0);
   if (roms->road.rom) {
      delete[]roms->road.rom;
      roms->road.rom = NULL;
   }
   enabled = true;
   return 1;
}

void Video::disable() {
   renderer->disable();
   enabled = false;
}

// Configure video settings from config file
// ─────────────────────────────────────────
int Video::set_video_mode(video_settings_t *settings) {
   if (settings->widescreen) {
      config.s16_width = S16_WIDTH_WIDE;
      config.s16_x_off = (S16_WIDTH_WIDE - S16_WIDTH)/2;
   } else {
      config.s16_width = S16_WIDTH;
      config.s16_x_off = 0;
   }
   config.s16_height = S16_HEIGHT;
// Internal video buffer is doubled in hi-res mode.
   if (settings->hires) {
      config.s16_width <<= 1;
      config.s16_height <<= 1;
   }
   if (settings->scanlines < 0) settings->scanlines = 0;
   else if (settings->scanlines > 100) settings->scanlines = 100;
   if (settings->scale < 1)
      settings->scale = 1;
   set_shadow_intensity(settings->shadow == 0? shadow::ORIGINAL: shadow::MAME);
   renderer->init(config.s16_width, config.s16_height, settings->scale, settings->mode, settings->scanlines);
   return 1;
}

// Shadow Colours.
// ───────────────
// 63% Intensity is the correct value derived from hardware as follows:
// 1/	Shadows are just an extra 220 ohm resistor that goes to ground when enabled.
// 2/	This is in parallel with the resistor-"DAC" (3.9k, 2k, 1k, 0.5k, 0.25k), and otherwise left floating.
//
// Static calculation example:
//	const float rDAC   = 1.f/(1.f/3900.f + 1.f/2000.f + 1.f/1000.f + 1.f/500.f + 1.f/250.f);
//	const float rShade = 220.f;
//	const float shadeAttenuation = rShade/(rShade + rDAC); // 0.63f
//
// (MAME uses an incorrect value which is closer to 78% Intensity)
void Video::set_shadow_intensity(float f) {
   renderer->set_shadow_intensity(f);
}

void Video::prepare_frame() {
// Renderer Specific Frame Setup
   if (!renderer->start_frame())
      return;
   if (!enabled) {
   // Fill with black pixels
      for (int i = 0; i < config.s16_width*config.s16_height; i++)
         pixels[i] = 0;
   } else {
   // OutRun Hardware Video Emulation
      tile_layer->update_tile_values();
      (hwroad.*hwroad.render_background)(pixels);
      tile_layer->render_tile_layer(pixels, 1, 0); // background layer
      tile_layer->render_tile_layer(pixels, 0, 0); // foreground layer
      if (!config.engine.fix_bugs || oroad.horizon_base != ORoad::HORIZON_OFF)
         (hwroad.*hwroad.render_foreground)(pixels);
      sprite_layer->render(8);
      tile_layer->render_text_layer(pixels, 1);
   }
}

void Video::render_frame() {
   renderer->draw_frame(pixels);
   renderer->finalize_frame();
}

bool Video::supports_window() {
   return renderer->supports_window();
}

bool Video::supports_vsync() {
   return renderer->supports_vsync();
}

// Text Handling Code
// ──────────────────
void Video::clear_text_ram() {
   for (Num4 i = 0; i <= 0xFFF; i++)
      tile_layer->text_ram[i] = 0;
}

void Video::write_text8(Num4 addr, const Num1 data) {
   tile_layer->text_ram[addr&0xFFF] = data;
}

void Video::write_text16(Num4 *addr, const Num2 data) {
   tile_layer->text_ram[*addr&0xFFF] = (data >> 8)&0xFF;
   tile_layer->text_ram[(*addr + 1)&0xFFF] = data&0xFF;
   *addr += 2;
}

void Video::write_text16(Num4 addr, const Num2 data) {
   tile_layer->text_ram[addr&0xFFF] = (data >> 8)&0xFF;
   tile_layer->text_ram[(addr + 1)&0xFFF] = data&0xFF;
}

void Video::write_text32(Num4 *addr, const Num4 data) {
   tile_layer->text_ram[*addr&0xFFF] = (data >> 24)&0xFF;
   tile_layer->text_ram[(*addr + 1)&0xFFF] = (data >> 16)&0xFF;
   tile_layer->text_ram[(*addr + 2)&0xFFF] = (data >> 8)&0xFF;
   tile_layer->text_ram[(*addr + 3)&0xFFF] = data&0xFF;
   *addr += 4;
}

void Video::write_text32(Num4 addr, const Num4 data) {
   tile_layer->text_ram[addr&0xFFF] = (data >> 24)&0xFF;
   tile_layer->text_ram[(addr + 1)&0xFFF] = (data >> 16)&0xFF;
   tile_layer->text_ram[(addr + 2)&0xFFF] = (data >> 8)&0xFF;
   tile_layer->text_ram[(addr + 3)&0xFFF] = data&0xFF;
}

Num1 Video::read_text8(Num4 addr) {
   return tile_layer->text_ram[addr&0xFFF];
}

// Tile Handling Code
// ──────────────────
void Video::clear_tile_ram() {
   for (Num4 i = 0; i <= 0xFFFF; i++)
      tile_layer->tile_ram[i] = 0;
}

void Video::write_tile8(Num4 addr, const Num1 data) {
   tile_layer->tile_ram[addr&0xFFFF] = data;
}

void Video::write_tile16(Num4 *addr, const Num2 data) {
   tile_layer->tile_ram[*addr&0xFFFF] = (data >> 8)&0xFF;
   tile_layer->tile_ram[(*addr + 1)&0xFFFF] = data&0xFF;
   *addr += 2;
}

void Video::write_tile16(Num4 addr, const Num2 data) {
   tile_layer->tile_ram[addr&0xFFFF] = (data >> 8)&0xFF;
   tile_layer->tile_ram[(addr + 1)&0xFFFF] = data&0xFF;
}

void Video::write_tile32(Num4 *addr, const Num4 data) {
   tile_layer->tile_ram[*addr&0xFFFF] = (data >> 24)&0xFF;
   tile_layer->tile_ram[(*addr + 1)&0xFFFF] = (data >> 16)&0xFF;
   tile_layer->tile_ram[(*addr + 2)&0xFFFF] = (data >> 8)&0xFF;
   tile_layer->tile_ram[(*addr + 3)&0xFFFF] = data&0xFF;
   *addr += 4;
}

void Video::write_tile32(Num4 addr, const Num4 data) {
   tile_layer->tile_ram[addr&0xFFFF] = (data >> 24)&0xFF;
   tile_layer->tile_ram[(addr + 1)&0xFFFF] = (data >> 16)&0xFF;
   tile_layer->tile_ram[(addr + 2)&0xFFFF] = (data >> 8)&0xFF;
   tile_layer->tile_ram[(addr + 3)&0xFFFF] = data&0xFF;
}

Num1 Video::read_tile8(Num4 addr) {
   return tile_layer->tile_ram[addr&0xFFFF];
}

// Sprite Handling Code
// ────────────────────
void Video::write_sprite16(Num4 *addr, const Num2 data) {
   sprite_layer->write(*addr&0xfff, data);
   *addr += 2;
}

// Palette Handling Code
// ─────────────────────
void Video::write_pal8(Num4 *palAddr, const Num1 data) {
   palette[*palAddr&0x1fff] = data;
   refresh_palette(*palAddr&0x1fff);
   *palAddr += 1;
}

void Video::write_pal16(Num4 *palAddr, const Num2 data) {
   Num4 adr = *palAddr&0x1fff;
   palette[adr] = (data >> 8)&0xFF;
   palette[adr + 1] = data&0xFF;
   refresh_palette(adr);
   *palAddr += 2;
}

void Video::write_pal32(Num4 *palAddr, const Num4 data) {
   Num4 adr = *palAddr&0x1fff;
   palette[adr] = (data >> 24)&0xFF;
   palette[adr + 1] = (data >> 16)&0xFF;
   palette[adr + 2] = (data >> 8)&0xFF;
   palette[adr + 3] = data&0xFF;
   refresh_palette(adr);
   refresh_palette(adr + 2);
   *palAddr += 4;
}

void Video::write_pal32(Num4 adr, const Num4 data) {
   adr &= 0x1fff;
   palette[adr] = (data >> 24)&0xFF;
   palette[adr + 1] = (data >> 16)&0xFF;
   palette[adr + 2] = (data >> 8)&0xFF;
   palette[adr + 3] = data&0xFF;
   refresh_palette(adr);
   refresh_palette(adr + 2);
}

Num1 Video::read_pal8(Num4 palAddr) {
   return palette[palAddr&0x1fff];
}

Num2 Video::read_pal16(Num4 palAddr) {
   Num4 adr = palAddr&0x1fff;
   return (palette[adr] << 8) | palette[adr + 1];
}

Num2 Video::read_pal16(Num4 *palAddr) {
   Num4 adr = *palAddr&0x1fff;
   *palAddr += 2;
   return (palette[adr] << 8) | palette[adr + 1];
}

Num4 Video::read_pal32(Num4 *palAddr) {
   Num4 adr = *palAddr&0x1fff;
   *palAddr += 4;
   return (palette[adr] << 24) | (palette[adr + 1] << 16) | (palette[adr + 2] << 8) | palette[adr + 3];
}

// Convert internal System 16 RRRR GGGG BBBB format palette to renderer output format
void Video::refresh_palette(Num4 palAddr) {
   palAddr &= ~1;
   Num4 a = (palette[palAddr] << 8) | palette[palAddr + 1];
   Num4 r = (a&0x000f) << 1; // r rrr0
   Num4 g = (a&0x00f0) >> 3; // g ggg0
   Num4 b = (a&0x0f00) >> 7; // b bbb0
   if ((a&0x1000) != 0)
      r |= 1; // r rrrr
   if ((a&0x2000) != 0)
      g |= 1; // g gggg
   if ((a&0x4000) != 0)
      b |= 1; // b bbbb
   renderer->convert_palette(palAddr, r, g, b);
}
