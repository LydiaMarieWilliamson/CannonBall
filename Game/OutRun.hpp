// OutRun Engine Entry Point.
//
// This is the hub of the ported OutRun code.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Types.hpp"
#include "ROMs.hpp"
#include "Globals.hpp"
#include "Video.hpp"
#include "Arena/Config.hpp"

// Main include for Ported OutRun Code
#include "Game/Addresses.hpp"
#include "Game/Sprites.hpp"
#include "Game/Road.hpp"
#include "Game/InitGame.hpp"
#include "Game/Sound/SoundInt.hpp"

// Globals
enum {
   GS_INIT = 0, // Initalize Game
   GS_ATTRACT = 1, // Attract Mode
   GS_INIT_BEST1 = 2, // Load Best Outrunners
   GS_BEST1 = 3, // Best Outrunners (Attract Mode)
   GS_INIT_LOGO = 4, // Load Outrun Logo
   GS_LOGO = 5, // Outrun Logo (Attract Mode)
   GS_INIT_MUSIC = 6, // Load Music Selection Screen
   GS_MUSIC = 7, // Music Selection Screen
   GS_INIT_GAME = 8, // Loading In-Game
   GS_START1 = 9, // Start Game, Car Driving In
   GS_START2 = 10, // Start Game, Countdown
   GS_START3 = 11, // Start Game, Countdown 2
   GS_INGAME = 12, // Start Game, User in control
   GS_INIT_BONUS = 13, // Load Bonus Points
   GS_BONUS = 14, // Display Bonus Points
   GS_INIT_GAMEOVER = 15, // Load Game Over
   GS_GAMEOVER = 16, // Game Over Text
   GS_INIT_MAP = 17, // Load Course Map
   GS_MAP = 18, // Course Map
   GS_INIT_BEST2 = 19, // Load Best Outrunners
   GS_BEST2 = 20, // Best Outrunners
   GS_REINIT = 21, // Reinitalize Game (after outrunners screen)
   GS_CALIBRATE_MOTOR = 100, // Calibrate Motors
};

struct time_trial_t {
   bool enabled; // Time Trial Mode Enabled
   Num1 level; // Time Trial Level
   Num1 traffic; // Max Traffic Level
   Num1 laps; // Total laps (maximum of 5 laps total allowed)
   Num1 current_lap; // Which lap are we currently on
   Num2 overtakes; // Number of overtakes
   Num2 vehicle_cols; // Number of vehicle collisions
   Num2 crashes; // Number of crashes
   Num1 laptimes[5][3]; // Stored lap times
   Int2 best_lap_counter; // Counter representing best laptime
   Num1 best_lap[3]; // Stored best lap time
   bool new_high_score; // Has player achieved a new high score?
};

// Addresses (Used to swap between original and Japanese roms)
struct adr_t {
// CPU 0
   Num4 tiles_def_lookup;
   Num4 tiles_table;
   Num4 sprite_master_table;
   Num4 sprite_type_table;
   Num4 sprite_def_props1;
   Num4 sprite_def_props2;
   Num4 sprite_cloud;
   Num4 sprite_minitree;
   Num4 sprite_grass;
   Num4 sprite_sand;
   Num4 sprite_stone;
   Num4 sprite_water;
   Num4 sprite_ferrari_frames;
   Num4 sprite_skid_frames;
   Num4 sprite_pass_frames;
   Num4 sprite_pass1_skidl;
   Num4 sprite_pass1_skidr;
   Num4 sprite_pass2_skidl;
   Num4 sprite_pass2_skidr;
   Num4 sprite_crash_spin1;
   Num4 sprite_crash_spin2;
   Num4 sprite_bump_data1;
   Num4 sprite_bump_data2;
   Num4 sprite_crash_man1;
   Num4 sprite_crash_girl1;
   Num4 sprite_crash_flip;
   Num4 sprite_crash_flip_m1;
   Num4 sprite_crash_flip_g1;
   Num4 sprite_crash_flip_m2;
   Num4 sprite_crash_flip_g2;
   Num4 sprite_crash_man2;
   Num4 sprite_crash_girl2;
   Num4 smoke_data;
   Num4 spray_data;
   Num4 shadow_data;
   Num4 shadow_frames;
   Num4 sprite_shadow_small;
   Num4 sprite_logo_bg;
   Num4 sprite_logo_car;
   Num4 sprite_logo_bird1;
   Num4 sprite_logo_bird2;
   Num4 sprite_logo_base;
   Num4 sprite_logo_text;
   Num4 sprite_logo_palm1;
   Num4 sprite_logo_palm2;
   Num4 sprite_logo_palm3;
   Num4 sprite_fm_left;
   Num4 sprite_fm_centre;
   Num4 sprite_fm_right;
   Num4 sprite_dial_left;
   Num4 sprite_dial_centre;
   Num4 sprite_dial_right;
   Num4 sprite_eq;
   Num4 sprite_radio;
   Num4 sprite_hand_left;
   Num4 sprite_hand_centre;
   Num4 sprite_hand_right;
   Num4 sprite_coursemap_top;
   Num4 sprite_coursemap_bot;
   Num4 sprite_coursemap_end;
   Num4 sprite_minicar_right;
   Num4 sprite_minicar_up;
   Num4 sprite_minicar_down;
   Num4 anim_seq_flag;
   Num4 anim_ferrari_curr;
   Num4 anim_ferrari_next;
   Num4 anim_pass1_curr;
   Num4 anim_pass1_next;
   Num4 anim_pass2_curr;
   Num4 anim_pass2_next;
   Num4 anim_ferrari_frames;
   Num4 anim_endseq_obj1;
   Num4 anim_endseq_obj2;
   Num4 anim_endseq_obj3;
   Num4 anim_endseq_obj4;
   Num4 anim_endseq_obj5;
   Num4 anim_endseq_obj6;
   Num4 anim_endseq_obj7;
   Num4 anim_endseq_obj8;
   Num4 anim_endseq_objA;
   Num4 anim_endseq_objB;
   Num4 anim_end_table;
   Num4 traffic_props;
   Num4 traffic_data;
   Num4 sprite_porsche;
   Num4 sprite_coursemap;
   Num4 road_seg_table;
   Num4 road_seg_end;
   Num4 road_seg_split;
// CPU 1
   Num4 road_height_lookup;
};

class OOutputs;

class Outrun {
public:
   OOutputs *outputs;
   bool freeze_timer;
// CannonBall Game Mode
   Num1 cannonball_mode;
   const static Num1 MODE_ORIGINAL = 0; // Original OutRun Mode
   const static Num1 MODE_TTRIAL = 1; // Enhanced Time Trial Mode
   const static Num1 MODE_CONT = 2; // Enhanced Continuous Mode
// Max traffic level for custom modes
   Num1 custom_traffic;
// Time trial data
   time_trial_t ttrial;
// Service Mode Toggle: Not implemented yet.
   bool service_mode;
// Tick Logic. Used when running at non-standard > 30 fps
   bool tick_frame;
// Tick Counter (always syncd to 30 fps to flash text and other stuff)
   Num4 tick_counter;
// Main game state
   Int1 game_state;
// Address structures
   adr_t adr;
   Outrun();
   ~Outrun();
   void init();
   void boot();
   void tick(bool tick_frame);
   void vint();
   void init_best_outrunners();
   void select_course(const bool jap, const bool prototype);
private:
   Num1 attract_view;
   Int2 attract_counter;
// Car Increment Backup for attract mode
   Num4 car_inc_bak;
// Debug to denote when fork has been chosen
   Int1 fork_chosen;
   void jump_table();
   void init_jump_table();
   void main_switch();
   void controls();
   bool decrement_timers();
   void init_motor_calibration();
   void init_attract();
   void tick_attract();
   void check_freeplay_start();
};
extern Outrun outrun;
