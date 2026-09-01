// Heads-Up Display (HUD) Code
// -	Score Rendering
// -	Timer Rendering
// -	Rev Rendering
// -	Minimap Rendering
// -	Text Rendering
//
// Copyright Chris White.
// See License.txt for more details.
#include <cstring>
#include "../Utils.hpp"
#include "Game/Ferrari.hpp"
#include "Game/Tools.hpp"
#include "Game/Display.hpp"
#include "Game/Outputs.hpp"
#include "Game/Stats.hpp"

OHud ohud;

OHud::OHud(void) {
}

OHud::~OHud(void) {
}

// Draw Text Labels For HUD
//
// At: b462
void OHud::draw_main_hud() {
   blit_text1(HUD_LAP1);
   blit_text1(HUD_LAP2);
   if (outrun.cannonball_mode == Outrun::MODE_ORIGINAL) {
      blit_text1(HUD_TIME1);
      blit_text1(HUD_TIME2);
      blit_text1(HUD_SCORE1);
      blit_text1(HUD_SCORE2);
      blit_text1(HUD_STAGE1);
      blit_text1(HUD_STAGE2);
      blit_text1(HUD_ONE);
      do_mini_map();
   } else if (outrun.cannonball_mode == Outrun::MODE_TTRIAL) {
      draw_score(translate(3, 2), 0, 2);
      blit_text1(2, 1, HUD_SCORE1);
      blit_text1(2, 2, HUD_SCORE2);
      blit_text_big(4, "TIME TO BEAT");
      draw_lap_timer(translate(16, 7), outrun.ttrial.best_lap, outrun.ttrial.best_lap[2]);
   } else if (outrun.cannonball_mode == Outrun::MODE_CONT) {
      blit_text1(HUD_TIME1);
      blit_text1(HUD_TIME2);
      blit_text1(HUD_SCORE1);
      blit_text1(HUD_SCORE2);
      blit_text1(HUD_STAGE1);
      blit_text1(HUD_STAGE2);
      blit_text1(HUD_ONE);
   }
}

void OHud::clear_timetrial_text() {
   blit_text_big(4, "            ");
   blit_text_new(16, 7, "            ");
}

void OHud::draw_fps_counter(Int2 fps) {
   std::string str = "FPS " + Utils::to_string(fps);
   blit_text_new(30, 0, str.c_str());
}

// Routine to setup and draw mini-map (bottom RHS of HUD)
//
// At: 8b52
void OHud::do_mini_map() {
   if (outrun.game_state == GS_ATTRACT)
      return;
   Num4 tile_addr = setup_mini_map();
   draw_mini_map(tile_addr);
}

// Setup Appropriate Tile Address For Minimap.
//
// Returns start address of block of 4 tiles. Represents square of route on mini-map screen.
//
// At: 8b68
Num4 OHud::setup_mini_map() {
   if (ostats.route_info > 0x4F)
      ostats.route_info = 0x4F;
// Map Route to appropriate tile
   const Num1 ROUTE_MAPPING[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
      0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06,
      0x07, 0x07, 0x08, 0x08, 0x09, 0x09, 0x0A, 0x0A, 0x0B, 0x0B, 0x0C, 0x0C, 0x0D, 0x0D, 0x0E, 0x0E,
      0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
   };
   return TILES_MINIMAP + (ROUTE_MAPPING[ostats.route_info] << 2);
}

void OHud::draw_mini_map(Num4 tile_addr) {
// Address in text ram to copy this to
   Num4 dst = 0x110CFA;
// Base Tile to use
   const Num2 BASE = 0x8B00;
   Num2 tile = (BASE | roms.rom0.read8(&tile_addr));
   video.write_text16(dst, tile);
   tile = BASE | roms.rom0.read8(&tile_addr);
   video.write_text16(2 + dst, tile);
   tile = BASE | roms.rom0.read8(&tile_addr);
   video.write_text16(0x80 + dst, tile);
   tile = BASE | roms.rom0.read8(&tile_addr);
   video.write_text16(0x82 + dst, tile);
}

// Print Timer To Top Left Hand Corner Of Screen
//
// At: 8216
void OHud::draw_timer1(Num2 time) {
   if (outrun.game_state < GS_START1 || outrun.game_state > GS_INGAME)
      return;
   if (!outrun.freeze_timer) {
      const Num2 BASE_TILE = 0x8C80;
      draw_timer2(time > 0x99? 0x99: time, 0x1100BE, BASE_TILE);
   // Blank out the OFF text area
      video.write_text16(0x110C2, 0);
      video.write_text16(0x110C2 + 0x80, 0);
   } else {
      Num4 dst_addr = translate(7, 1);
      const Num2 PAL = 0x8AA0;
      const Num2 O = (('O' - 0x41)*2) + PAL; // Convert character to real index (D0-0x41) so A is 0x01
      const Num2 F = (('F' - 0x41)*2) + PAL;
      video.write_text16(&dst_addr, O); // Write first row to text ram
      video.write_text16(0x7E + dst_addr, O + 1); // Write second row to text ram
      video.write_text16(&dst_addr, F); // Write first row to text ram
      video.write_text16(0x7E + dst_addr, F + 1); // Write second row to text ram
      video.write_text16(&dst_addr, F); // Write first row to text ram
      video.write_text16(0x7E + dst_addr, F + 1); // Write second row to text ram
   }
}

// Called directly by High Score Table
//
// At: 8234
void OHud::draw_timer2(Num2 time_counter, Num4 addr, Num2 base_tile) {
   Num2 digit1 = time_counter&0xF;
   Num2 digit2 = (time_counter&0xF0) >> 4;
// Low Digit
   Num2 value = (digit1 << 1) + base_tile;
   video.write_text16(0x02 + addr, value);
   video.write_text16(0x82 + addr, value + 1);
// High Digit
   value = (digit2 << 1);
   if (value) {
      value += base_tile;
      video.write_text16(0x00 + addr, value);
      video.write_text16(0x80 + addr, value + 1);
   } else {
      video.write_text16(0x00 + addr, 0);
      video.write_text16(0x80 + addr, 0);
   }
}

void OHud::draw_lap_timer(Num4 addr, Num1 *digits, Num1 ms_value) {
   const Num2 BASE = 0x8230;
   const Num2 APOSTROPHE1 = 0x835E;
   const Num2 APOSTROPHE2 = 0x835F;
// Write Minute Digit
   video.write_text16(&addr, BASE | digits[0]);
   video.write_text16(&addr, APOSTROPHE1);
// Write Seconds
   video.write_text16(&addr, BASE | (digits[1]&0xF0) >> 4);
   video.write_text16(&addr, BASE | (digits[1]&0xF));
   video.write_text16(&addr, APOSTROPHE2);
// Write Milliseconds
   video.write_text16(&addr, BASE | (ms_value&0xF0) >> 4);
   video.write_text16(&addr, BASE | (ms_value&0xF));
}

// Draw Score (In-Game HUD)
//
// At: 7382
void OHud::draw_score_ingame(Num4 score) {
   if (outrun.game_state < GS_START1 || outrun.game_state > GS_BONUS)
      return;
   draw_score(0x110150, score, 2);
}

// Draw Score
//
//	+ 8530 = Digit 0
//	+ 8531 = Digit 1
//
// At: 7146
void OHud::draw_score(Num4 addr, const Num4 score, Num1 font) {
// Base address of Digit 0 setup here
   const Num2 BASE = 0x30 | (font << 9) | 0x8100;
// Blank tile for comparison purposes
   const Num2 BLANK = 0x8020;
   Num1 *digits = new Num1[8];
// Topmost digit
   digits[0] = ((score >> 16)&0xF000) >> 12;
   digits[1] = ((score >> 16)&0xF00) >> 8;
   digits[2] = ((score >> 16)&0xF0) >> 4;
   digits[3] = ((score >> 16)&0xF);
   digits[4] = (score&0xF000) >> 12;
   digits[5] = (score&0xF00) >> 8;
   digits[6] = (score&0xF0) >> 4;
   digits[7] = (score&0xF);
   bool found = false;
// Draw blank digits until we find first digit
// Then use zero for blank digits
   for (Num1 i = 0; i < 7; i++) {
      if (!found && !digits[i])
         video.write_text16(&addr, BLANK);
      else {
         video.write_text16(&addr, digits[i] + BASE);
         found = true;
      }
   }
   video.write_text16(&addr, digits[7] + BASE); // Always draw last digit
   delete[]digits;
}

// Same as above function but writes to tile ram instead.
// Not an ideal solution, really a workaround because text and tile ram are not one big lump in my implementation
void OHud::draw_score_tile(Num4 addr, const Num4 score, Num1 font) {
// Base address of Digit 0 setup here
   const Num2 BASE = 0x30 | (font << 9) | 0x8100;
// Blank tile for comparison purposes
   const Num2 BLANK = 0x8020;
   Num1 *digits = new Num1[8];
// Topmost digit
   digits[0] = ((score >> 16)&0xF000) >> 12;
   digits[1] = ((score >> 16)&0xF00) >> 8;
   digits[2] = ((score >> 16)&0xF0) >> 4;
   digits[3] = ((score >> 16)&0xF);
   digits[4] = (score&0xF000) >> 12;
   digits[5] = (score&0xF00) >> 8;
   digits[6] = (score&0xF0) >> 4;
   digits[7] = (score&0xF);
   bool found = false;
// Draw blank digits until we find first digit
// Then use zero for blank digits
   for (Num1 i = 0; i < 7; i++) {
      if (!found && !digits[i])
         video.write_tile16(&addr, BLANK);
      else {
         video.write_tile16(&addr, digits[i] + BASE);
         found = true;
      }
   }
   video.write_tile16(&addr, digits[7] + BASE); // Always draw last digit
   delete[]digits;
}

// Modified Version Of Draw Digits
//
// At: c3a0
void OHud::draw_stage_number(Num4 addr, Num1 digit, Num2 col) {
   if (digit < 10) {
      video.write_text16(addr, digit + (col << 8) + DIGIT_BASE);
   } else {
      int hex = outils::convert16_dechex(digit);
      video.write_text16(addr + 2, (hex&0xF) + (col << 8) + DIGIT_BASE);
      video.write_text16(addr, (hex >> 4) + (col << 8) + DIGIT_BASE);
   }
}

// Draw Rev Counter
//
// At: 6b08
void OHud::draw_rev_counter() {
// Return in attract mode and don't draw rev counter
   if (outrun.game_state <= GS_INIT_GAME) return;
   Num2 revs = oferrari.rev_stop_flag? oferrari.revs_post_stop: oferrari.revs >> 16;
// Boost revs during countdown phase, so the bar goes further into the red
   if (oinitengine.car_increment >> 16 == 0)
      revs += (revs >> 2);
   revs >>= 4;
   Num4 addr = 0x110DB4; // Address of rev counter
   const Num2 REV_OFF = 0x8120; // Rev counter: Off (Blank Tile)
   const Num2 REV_ON1 = 0x81FE; // Rev counter: On (Single Digit)
   const Num2 REV_ON2 = 0x81FD; // Rev counter: On (Double Digit)
   const Num2 GREEN = 0x200;
   const Num2 WHITE = 0x400;
   const Num2 RED = 0x600;
   for (Int1 i = 0; i <= 0x13; i++) {
      Num2 tile = 0;
      if (revs > i) {
         tile = REV_ON2;
         if (i >= 0xE) tile |= RED;
         else if (i <= 9) tile |= WHITE;
         else tile |= GREEN;
      } else if (revs != i) {
         tile = REV_OFF | WHITE;
      } else {
         tile = REV_ON1;
         if (i >= 0xE) tile |= RED;
         else if (i <= 9) tile |= WHITE;
         else tile |= GREEN;
      }
      video.write_text16(addr, tile);
   // On odd indexes, we don't increment to next word - to effectively shorten the length of the rev counter
   // It would be twice as long otherwise
      if (i&1)
         addr += 2;
   }
   oferrari.rev_pitch2 = oferrari.rev_pitch1;
}

// Convert & Blit car speed to screen
//
// At: bb72
void OHud::blit_speed(Num4 dst_addr, Num2 speed) {
   const Num2 TILE_BASE = 0x8C60; // Base tile number
// Convert to human readable speed
   speed = outils::convert16_dechex(speed);
   Num2 digit1 = speed&0xF;
   Num2 digit2 = (speed&0xF0) >> 4;
   Num2 digit3 = (speed&0xF00) >> 8;
   digit3 <<= 1;
   if (digit3 == 0) {
      digit2 <<= 1;
      if (digit2 != 0)
         digit2 += TILE_BASE;
   } else {
      digit3 += TILE_BASE;
      digit2 <<= 1;
      digit2 += TILE_BASE;
   }
// Blit Top Line Of Tiles
   digit1 <<= 1;
   digit1 += TILE_BASE;
   video.write_text16(&dst_addr, digit3);
   video.write_text16(&dst_addr, digit2);
   video.write_text16(dst_addr, digit1);
   dst_addr += 0x7C; // Set to next horizontal line of number tiles
// Blit Bottom Line Of Tiles
   if (digit3 != 0) digit3++;
   if (digit2 != 0) digit2++;
   digit1++;
   video.write_text16(&dst_addr, digit3);
   video.write_text16(&dst_addr, digit2);
   video.write_text16(dst_addr, digit1);
}

// Blit large digit spanning two rows.
//
// At: 9bf2
void OHud::blit_large_digit(Num4 *addr, Num1 digit) {
   video.write_text16(*addr, (digit + 0x80) | 0x8C00);
   video.write_text16(*addr + 0x80, (digit + 0x81) | 0x8C00);
   *addr += 2;
}

// Draw Copyright Text to text ram
//
// At: b844
// Input:	None
// Output:	None
void OHud::draw_copyright_text() {
   blit_text1(TEXT1_1986_SEGA);
   blit_text1(TEXT1_COPYRIGHT);
}

// Draw Insert Coin text
//
// At: b7d0
void OHud::draw_insert_coin() {
// Update text
   if ((outrun.tick_counter ^ (outrun.tick_counter - 1))&BIT_4) {
   // Flash Press Start
      if (ostats.credits) {
         if (outrun.tick_counter&BIT_4) {
            blit_text1(TEXT1_PRESS_START);
            outrun.outputs->set_digital(OOutputs::D_START_LAMP);
         } else {
            blit_text1(TEXT1_CLEAR_START);
            outrun.outputs->clear_digital(OOutputs::D_START_LAMP);
         }
      }
   // Flash Insert Coins / Freeplay Press Start
      else {
         if (config.engine.freeplay) {
            Num4 dst_addr = 0x110ACC;
            const static Num1 PRESS_START[] = { 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x28 };
            if (outrun.tick_counter&BIT_4) {
            // Blit each tile
               for (Num2 i = 0; i < sizeof(PRESS_START); i++)
                  video.write_text16(&dst_addr, (0x8700 | PRESS_START[i]));
            } else {
               for (Num2 i = 0; i < sizeof(PRESS_START); i++)
                  video.write_text16(&dst_addr, (0x8700 | 0x20));
            }
         } else {
            blit_text1((outrun.tick_counter&BIT_4)? TEXT1_INSERT_COINS: TEXT1_CLEAR_COINS);
         }
      }
   }
}

// At: 6cde
void OHud::draw_credits() {
   if (config.engine.freeplay) {
      blit_text1(TEXT1_FREEPLAY);
   } else {
      video.write_text16(0x110D44, ostats.credits | 0x8630); // blit digit
      blit_text1(ostats.credits >= 2? TEXT1_CREDITS: TEXT1_CREDIT);
   }
}

// Blit Tiles to text ram layer (Single Row)
//
// At: b844
// Input:	Source address in rom of data format
// Output:	None
//
// Format of the input data is as follows:
//	Long 1: Destination address to move data to. [e.g. 0x00110D34 which would go to the text ram]
//	Word 1: Number of tiles to draw / counter
//	Byte 1: High byte to apply to every copy, containing priority info [86]
//	Byte 2: Not used
//
//	Byte 3: Second byte to copy containing tile number (low)
//	Byte 4: Third byte to copy containing tile number (low)
//	Byte 5: etc.
//
// Text layer name table format:
//	MSB          LSB
//	p???cccnnnnnnnnn
//	p : Priority.	If 0, sprites with priority level 3 are shown over the text.
//			If 1, the text layer is shown over sprites regardless of priority.
//	c : Color palette
//	n : Tile index to use
//	? : Unknown
void OHud::blit_text1(Num4 src_addr) {
   Num4 dst_addr = roms.rom0.read32(&src_addr); // Text RAM destination address
   Num2 counter = roms.rom0.read16(&src_addr); // Number of tiles to blit
   Num2 data = roms.rom0.read16(&src_addr); // Tile data to blit
// Blit each tile
   for (Num2 i = 0; i <= counter; i++) {
      data = (data&0xFF00) | roms.rom0.read8(&src_addr);
      video.write_text16(&dst_addr, data);
   }
}

void OHud::blit_text1(Num1 x, Num1 y, Num4 src_addr) {
   Num4 dst_addr = translate(x, y);
   src_addr += 4;
   Num2 counter = roms.rom0.read16(&src_addr); // Number of tiles to blit
   Num2 data = roms.rom0.read16(&src_addr); // Tile data to blit
// Blit each tile
   for (Num2 i = 0; i <= counter; i++) {
      data = (data&0xFF00) | roms.rom0.read8(&src_addr);
      video.write_text16(&dst_addr, data);
   }
}

// Blit Tiles to text ram layer (Double Row)
//
// At: b844
// Input:	Source address in rom of data format
// Output:	None
//
// Format of the input data is as follows:
//	Byte 0: Offset into text RAM [First 2 bytes]
//	Byte 1: Offset into text RAM [First 2 bytes]
//	Byte 2: Palette to use
//	Byte 3: Number of characters to display (used as a counter)
//	Byte 4: Start of text to display
void OHud::blit_text2(Num4 src_addr) {
   Num4 dst_addr = 0x110000 + roms.rom0.read16(&src_addr); // Text RAM destination address
   Num2 pal = roms.rom0.read8(&src_addr);
   pal = 0x80A0 | ((pal << 9) | (pal >> 7)&1);
// same as ror 7 and extending to word
   Num2 counter = roms.rom0.read8(&src_addr); // Number of tiles to blit
// Blit each tile
   for (Num2 i = 0; i <= counter; i++) {
      Num2 data = roms.rom0.read8(&src_addr); // Tile data to blit
   // Blank space
      if (data == 0x20) {
         data = 0;
         video.write_text16(&dst_addr, data); // Write blank space to text ram
      }
   // Normal character
      else {
      // Convert character to real index (D0-0x41) so A is 0x01
         data -= 0x41;
         data = (data*2) + pal;
         video.write_text16(&dst_addr, data); // Write first row to text ram
         data++;
      }
      video.write_text16(0x7E + dst_addr, data); // Write second row to text ram
   }
}

// Enhanced Cannonball Routines Below
// ──────────────────────────────────

void OHud::draw_debug_info(Num4 pos, Num2 height_pat, Num1 sprite_pat) {
   ohud.blit_text_new(0, 4, "LEVEL POS", OHud::GREEN);
   ohud.blit_text_new(16, 4, "    ");
   ohud.blit_text_new(16, 4, Utils::to_string((int)(pos >> 16)).c_str(), OHud::PINK);
   ohud.blit_text_new(0, 5, "HEIGHT PATTERN", OHud::GREEN);
   ohud.blit_text_new(16, 5, "    ");
   ohud.blit_text_new(16, 5, Utils::to_string((int)height_pat).c_str(), OHud::PINK);
   ohud.blit_text_new(0, 6, "SPRITE PATTERN", OHud::GREEN);
   ohud.blit_text_new(16, 6, "    ");
   ohud.blit_text_new(16, 6, Utils::to_string((int)sprite_pat).c_str(), OHud::PINK);
}

// Big Yellow Text. Always Centered.
void OHud::blit_text_big(const Num1 Y, const char *text, bool do_notes) {
   Num2 length = (Num2)strlen(text);
   const Num2 X = 20 - (length >> 1);
// Clear complete row in text ram before blitting
   for (Num1 x = 0; x < 40; x++) {
      video.write_text16(translate(x, Y) + 0x110000, 0); // Write blank space to text ram
      video.write_text16(translate(x, Y) + 0x11007E, 0); // Write blank space to text ram
   }
// Draw Notes
   if (do_notes) {
   // Note tiles to append to left side of text
      const Num4 NOTE_TILES1 = 0x8A7A8A7B;
      const Num4 NOTE_TILES2 = 0x8A7C8A7D;
      video.write_text32(translate(X - 2, Y) + 0x110000, NOTE_TILES1);
      video.write_text32(translate(X - 2, Y) + 0x110080, NOTE_TILES2);
   }
   Num4 dst_addr = translate(X, Y) + 0x110000;
// Blit each tile
   for (Num2 i = 0; i < length; i++) {
      char c = *text++;
   // Convert lowercase characters to uppercase
      if (c >= 'a' && c <= 'z')
         c -= 0x20;
   // Numerals: Use different palette for numbers so they display more nicely
      else if (c >= '0' && c <= '9') {
         const Num2 pal = 0x8CA0;
         c -= 0x40;
         c = (c*2);
         video.write_text16(&dst_addr, c + pal); // Write first row to text ram
         video.write_text16(0x7E + dst_addr, c + pal + 1); // Write second row to text ram
      }
   // Blank space
      else if (c == ' ') {
         c = 0;
         video.write_text16(&dst_addr, c); // Write blank space to text ram
         video.write_text16(0x7E + dst_addr, c); // Write blank space to text ram
      }
   // Normal character
      if (c >= 'A' && c <= 'Z') {
         const Num2 pal = do_notes? 0x8AA0: 0x8CA0;
      // Convert character to real index (D0-0x41) so A is 0x01
         c -= 0x41;
         c = (c*2);
         video.write_text16(&dst_addr, c + pal); // Write first row to text ram
         video.write_text16(0x7E + dst_addr, c + pal + 1); // Write second row to text ram
      }
   }
}

// Custom Routine To Blit Text Easily
//
// The name table is 64×28, but only 40×28 is shown.
// The viewable portion of the name table starts at column 24 and goes to column 63, which maps to screen columns 0 through 39.
//
// Normal font: 41 onwards
void OHud::blit_text_new(Num2 x, Num2 y, const char *text, Num2 pal) {
   Num4 dst_addr = translate(x, y);
   Num2 length = (Num2)strlen(text);
   for (Num2 i = 0; i < length; i++) {
      char c = *text++;
   // Convert lowercase characters to uppercase
      if (c >= 'a' && c <= 'z')
         c -= 0x20;
      else if (c == '\xa9') // '\xa9' = '©'
         c = 0x10;
      else if (c == '-')
         c = 0x2d;
      else if (c == '.')
         c = 0x5b;
      video.write_text16(&dst_addr, (pal << 8) | c);
   }
}

// Translate x, y column position to tilemap address
// Base Position defaults to 0, 0
Num4 OHud::translate(Num2 x, Num2 y, const Num4 BASE_POS) {
   if (x > 63) x = 63;
   if (y > 27) y = 27;
// Calculate destination address based on x, y position
   return BASE_POS + ((x + (y*64)) << 1);
}
