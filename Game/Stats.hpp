// In-Game Statistics.
// -	Stage Timers
// -	Route Info
// -	Speed to Score Conversion
// -	Bonus Time Increment
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "OutRun.hpp"

class OStats {
public:
// Current stage
//	+0 = Stage 1
//	+1 = Stage 2
//	+2 = Stage 3
//	+3 = Stage 4
//	+4 = Stage 5
//	-1 = Bonus Points Section
//
// A good way to quickly see the end sequence is to set this to '4' and play through the first level.
   Int1 cur_stage;
// Score (Outputs Hex values directly)
   Num4 score;
// Store info on the route taken by the player
//	+10 For each stage.
//
// Then increment by the following when Left Hand route selected at each stage.
//	Stage 1 = +8 (1 << 3 - 0)
//	Stage 2 = +4 (1 << 3 - 1)
//	Stage 3 = +2 (1 << 3 - 2)
//	Stage 4 = +1 (1 << 3 - 3)
//	Stage 5 = Road doesn't split on this stage
//
// So if we reach Stage 2 (left route) we do 10 + 8 = 18
   Num2 route_info;
// Stores route_info for each stage. Used by course map screen
// First entry stores upcoming stage number
   Num2 routes[0x8];
// Frame Counter Reset/Load Value.
// Load frame counter with this value when the counter has decremented and expired.
// Note: Values stored and used in hex.
   Int2 frame_counter;
   const static Int2 frame_reset = 30;
// Time Counter (Frames). Counts downwards from 30.
// Used in correspondence with 0x60860.
// Note: Values stored and used in hex.
   Int2 time_counter;
// Extend Play Timer.
//
// Loaded to 0x80 when EXTEND PLAY! banner should flash
   Int2 extend_play_timer;
// Time data array
   static const Num1 TIME[];
// Counters that increment with each game tick.
// Each stage has an independent counter (increased to 15 from 5 to support continuous mode)
   Int2 stage_counters[15];
// Set when game completed
   bool game_completed;
   const Num1 *lap_ms;
// Number of credits inserted
   Num1 credits;
// Each stage has an entry for minutes, seconds and MS. (Extended to 15 from 5 to support continuous mode)
   Num1 stage_times[15][3];
   OStats(void);
   ~OStats(void);
   void init(bool);
   void clear_stage_times();
   void clear_route_info();
   void do_mini_map();
   void do_timers();
   void convert_speed_score(Num2);
   void update_score(Num4);
   void init_next_level();
private:
// Converted Stage Millisecond Value
   Num1 ms_value;
   void inc_lap_timer();
};
extern OStats ostats;
