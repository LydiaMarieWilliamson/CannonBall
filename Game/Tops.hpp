// Best Outrunners Name Entry & Display.
// Used in attract mode, and at game end.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Types.hpp"

struct score_entry {
   Num4 score;
   Num1 initial1;
   Num1 initial2;
   Num1 initial3;
   Num4 maptiles;
   Num2 time;
};

class OHiScore {
public:
// Number of score entries in table
   const static Num1 NO_SCORES = 20;
// 20 Score Entries
   score_entry scores[NO_SCORES];
   OHiScore(void);
   ~OHiScore(void);
   void init();
   void init_def_scores();
   void tick();
   void setup_pal_best();
   void setup_road_best();
   void display_scores();
private:
   const static Num2 TILE_PROPS = 0x8030;
// +C : Best OutRunners State
   Num1 best_or_state;
// +14: State of score logic
   Num1 state;
// +16: High Score Position In Table
   Int1 score_pos;
// +17 Selected Initial (0-2)
   Int1 initial_selected;
// +18: Selected Letter
   Int2 letter_selected;
// +1A: Acceleration Value Current
   Int2 acc_curr;
// +1C: Acceleration Value Previous
   Int2 acc_prev;
// +1E: Steering Value
   Int2 steer;
// +22: Flashing counter
   Num1 flash;
// +24: Total number of minicars that have reached destination
   Int1 dest_total;
// +26: High Score Table Display Position
   Int1 score_display_pos;
   enum {
      STATE_GETPOS, // Detect Score Position, Insert Score, Init Table
      STATE_DISPLAY, // Display Basic High Score Table
      STATE_ENTRY, // Init Name Entry
      STATE_DONE // Score Done
   };
// Mini-car data format.
// These are the mini cars that move across and reveal the high score entries
   struct minicar_entry {
      Int2 pos; // [+0] Word 0: Position
      Int2 speed; // [+2] Word 1: Speed (increments over time)
      Int2 base_speed; // [+4] Word 2: Base Speed
      Int2 dst_reached; // [+6] Word 3: Set when reached destination
      Num2 tile_props; // [+8] Word 4: Palette/Priority bits for tile
   };
// Number of minicar entries
   const static Num1 NO_MINICARS = 7;
// 20 Score Entries
   minicar_entry minicars[NO_MINICARS];
// Stores Laptime conversion
//	+0: Minutes Digit 1
//	+1: Minutes Digit 2
//	+2: Seconds Digit 1
//	+3: Seconds Digit 2
//	+4: Milliseconds Digit 1
//	+5: Milliseconds Digit 2
   Num2 laptime[6];
   void get_score_pos();
   void insert_score();
   void set_display_pos();
   void check_name_entry();
   Num4 get_score_adr();
   void blit_alphabet();
   void flash_entry(Num4 adr);
   void do_input(Num4 adr);
   Int1 read_controls();
   void setup_minicars();
   void tick_minicars();
   void setup_minicars_pal(minicar_entry *);
   void blit_score_table();
   void blit_scores();
   void blit_digit();
   void blit_initials();
   void blit_route_map();
   void blit_lap_time();
   void convert_lap_time(Num2);
};
extern OHiScore ohiscore;
