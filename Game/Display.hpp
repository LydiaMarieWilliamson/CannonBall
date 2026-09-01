// Heads-Up Display (HUD) Code
// -	Score Rendering
// -	Timer Rendering
// -	Rev Rendering
// -	Minimap Rendering
// -	Text Rendering
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "OutRun.hpp"

class OHud {
public:
// Colours for default text palette
   enum {
      GREY = 0x84,
      PINK = 0x86,
      GREEN = 0x92,
   } colors;
// Base for digits, for fast digit drawing
   const static Num2 DIGIT_BASE = 0x30;
   OHud(void);
   ~OHud(void);
   void draw_main_hud();
   void draw_fps_counter(Int2);
   void clear_timetrial_text();
   void do_mini_map();
   void draw_timer1(Num2);
   void draw_timer2(Num2, Num4, Num2);
   void draw_lap_timer(Num4, Num1 *, Num1);
   void draw_score_ingame(Num4);
   void draw_score(Num4, const Num4, const Num1);
   void draw_score_tile(Num4, const Num4, const Num1);
   void draw_stage_number(Num4, Num1, Num2 col = GREEN);
   void draw_rev_counter();
   void draw_debug_info(Num4 pos, Num2 height_pat, Num1 sprite_pat);
   void blit_text1(Num4);
   void blit_text1(Num1 x, Num1 y, Num4 src_addr);
   void blit_text2(Num4);
   void blit_text_big(const Num1 Y, const char *text, bool do_notes = false);
   void blit_text_new(Num2, Num2, const char *text, Num2 col = GREY);
   void blit_speed(Num4, Num2);
   void blit_large_digit(Num4 *, Num1);
   void draw_copyright_text();
   void draw_insert_coin();
   void draw_credits();
   Num4 setup_mini_map();
   Num4 translate(const Num2 x, const Num2 y, const Num4 BASE_POS = 0x110030);
private:
   void draw_mini_map(Num4);
};
extern OHud ohud;
