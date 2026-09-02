// Ferrari Rendering & Handling Code.
//
// Much of the handling code is very messy.
// As such, the translated code isn't great as I tried to focus on accuracy rather than refactoring.
//
// A good example of the randomness is a routine I've named
//	do_sound_score_slip()
// which performs everything from updating the score, setting the audio engine tone, triggering smoke effects etc. in an interwoven fashion.
//
// The Ferrari sprite has different properties to other game objects
// As there's only one of them, I've rolled the additional variables into this class.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Game/OutRun.hpp"

class OFerrari {
public:
// Ferrari Sprite Object
   oentry *spr_ferrari;
// Passenger 1 Sprite Object
   oentry *spr_pass1;
// Passenger 2 Sprite Object
   oentry *spr_pass2;
// Ferrari Shadow Sprite Object
   oentry *spr_shadow;
// Ferrari Colours
// ───────────────
// Palette to use (change Ferrari colours)
   Num2 ferrari_pal;
   const static Num2 PAL_RED = 2;
   const static Num2 PAL_BLUE = 256;
   const static Num2 PAL_YELLOW = 261;
   const static Num2 PAL_GREEN = 266;
   const static Num2 PAL_CYAN = 271;
// Main Switch Variables
// ─────────────────────
   enum {
   // Initialise Intro Animation Sequences
      FERRARI_SEQ1 = 0,
   // Tick Intro Animation Sequences
      FERRARI_SEQ2 = 1,
   // Initialize In-Game Logic
      FERRARI_INIT = 2,
   // Tick In-Game Logic
      FERRARI_LOGIC = 3,
   // Ferrari End Sequence Logic
      FERRARI_END_SEQ = 4,
   };
// Which routine is in use
   Num1 state;
// Unused counter. Implemented on original game so could be useful for debug.
   Num2 counter;
   Int2 steering_old;
   bool car_ctrl_active;
// Car State
//	-1	= Animation Sequence (Crash / Drive In)
//	0	= Normal
//	+1	= Smoke from wheels
   Int1 car_state;
   enum { CAR_ANIM_SEQ = -1, CAR_NORMAL = 0, CAR_SMOKE = 1 };
// Auto breaking for end sequence
   bool auto_brake;
// Torque table index lookup
//	00 = Start line only
//	10 = Low gear
//	1F = High gear
//
// Increments between the values
//
// Gets set based on what gear we're in
   Num1 torque_index;
   Int2 torque;
   Int4 revs;
// Rev Shift Value. Normal = 1.
// Higher values result in reaching higher revs faster!
   Num1 rev_shift;
// State of car wheels
//	0 = On Road
//	1 = Left Wheel Off-Road
//	2 = Right Wheel Off-Road
//	3 = Both Wheels Off-Road
   Num1 wheel_state;
   enum {
      WHEELS_ON = 0,
      WHEELS_LEFT_OFF = 1,
      WHEELS_RIGHT_OFF = 2,
      WHEELS_OFF = 3
   };
// Wheel Traction
//	0 = Both Wheels Have Traction
//	1 = One Wheel Has Traction
//	2 = No Wheels Have Traction
   Num1 wheel_traction;
   enum {
      TRACTION_ON = 0,
      TRACTION_HALF = 1,
      TRACTION_OFF = 2,
   };
// Ferrari is slipping/skidding either after collision or round bend
   Num2 is_slipping;
// Slip Command Sent To Sound Hardware
   Num1 slip_sound;
// Stores previous value of car_increment
   Num2 car_inc_old;
// Difference between car_x_pos and car_x_old
   Int2 car_x_diff;
// Engine Stop Flag
// ────────────────
// Flag set when switching back to in-game engine, to be used with revs_post_stop
// This is used to adjust the rev boost when returning to game
   Int2 rev_stop_flag;
// Rev boost when we switch back to ingame engine and hand user control.
// Set by user being on revs before initialization.
   Int2 revs_post_stop;
   Int2 acc_post_stop;
// Engine Sounds. Probably needs to be moved
// ─────────────────────────────────────────
// Sound: Adjusted rev value (to be used to set pitch sound fx)
   Num2 rev_pitch1;
   Num2 rev_pitch2;
// Ferrari Specific Values
// ───────────────────────
// *22 [Word] AI Curve Counter. Increments During Curve. Resets On Straight.
   Int2 sprite_ai_counter;
// *24 [Word] AI Curve Value. 0x96 - curve_next.
   Int2 sprite_ai_curve;
// *26 [Word] AI X Position Adjustment
   Int2 sprite_ai_x;
// *28 [Word] AI Steering Adjustment
   Int2 sprite_ai_steer;
// *2A [Word] Car X Position Backup
   Int2 sprite_car_x_bak;
// *2C [Word] Wheel State
   Int2 sprite_wheel_state;
// *2E [Word] Ferrari Slipping (Copy of slip counter)
   Int2 sprite_slip_copy;
// *39 [Byte] Wheel Palette Offset
   Int1 wheel_pal;
// *3A [Word] Passenger Y Offset
   Int2 sprite_pass_y;
// *3C [Word] Wheel Frame Counter Reset
   Int2 wheel_frame_reset;
// *3E [Word] Wheel Frame Counter Reset
   Int2 wheel_counter;
   OFerrari(void);
   ~OFerrari(void);
   void init(oentry *, oentry *, oentry *, oentry *);
   void reset_car();
   void init_ingame();
   void tick();
   void set_ferrari_x();
   void set_ferrari_bounds();
   void check_wheels();
   void set_curve_adjust();
   void draw_shadow();
   void move();
   void do_sound_score_slip();
   void shake();
   void do_skid();
private:
// Max speed of car
   const static Num4 MAX_SPEED = 0x1260000;
// Car Base Increment, For Movement
   const static Num4 CAR_BASE_INC = 0x12F;
// Maximum distance to allow car to stray from road
   const static Num2 OFFROAD_BOUNDS = 0x1F4;
// Used by set_car_x
   Int2 road_width_old;
// Controls
// ────────
   Int2 accel_value;
   Int2 accel_value_bak;
   Int2 brake_value;
   bool gear_value;
   bool gear_bak;
// Trickle down adjusted acceleration values
   Int2 acc_adjust1;
   Int2 acc_adjust2;
   Int2 acc_adjust3;
// Trickle down brake values
   Int2 brake_adjust1;
   Int2 brake_adjust2;
   Int2 brake_adjust3;
// Calculated brake value to subtract from acc_burst.
   Int4 brake_subtract;
// Counter. When enabled, acceleration disabled
   Int1 gear_counter;
// Previous rev adjustment (stored)
   Int4 rev_adjust;
// Smoke
// ─────
// Counter for smoke after changing gear. Values over 0 result in smoke
   Int2 gear_smoke;
// Similar to above
   Int2 gfx_smoke;
// Set to -1 when car sharply corners and player is steering into direction of corner
   Int1 cornering;
   Int1 cornering_old;
   static Num2 torque_lookup[];
   static const Num1 rev_inc_lookup[];
   void logic();
   void ferrari_normal();
   void setup_ferrari_sprite();
   void setup_ferrari_bonus_sprite();
   void init_end_seq();
   void do_end_seq();
   void tick_engine_disabled(Int4 &);
   void set_ferrari_palette();
   void set_passenger_sprite(oentry *);
   void set_passenger_frame(oentry *);
   void car_acc_brake();
   void do_gear_torque(Int2 &);
   void do_gear_low(Int2 &);
   void do_gear_high(Int2 &);
   Int4 tick_gear_change(Int2);
   Int4 get_speed_inc_value(Num2, Num4);
   Int4 get_speed_dec_value(Num2);
   void set_brake_subtract();
   void finalise_revs(Int4 &, Int4);
   void convert_revs_speed(Int4, Int4 &);
   void update_road_pos();
   Int4 tick_smoke();
   void set_wheels(Num1);
   inline void draw_sprite(oentry *);
};
extern OFerrari oferrari;
