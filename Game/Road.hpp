// Road Rendering & Control
//
// This is a complete port of the 68000 SUB CPU Program ROM.
//
// The original code consists of a shared Sega library and some routines which are OutRun specific.
//
// Some of the original code is not used and is therefore not ported.
//
// This is the most complex area of the game code, and an area of the code in need of refactoring.
//
// Useful background reading on road rendering:
//	http://www.extentofthejam.com/pseudo/
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

class ORoad {
public:
   Num4 road_pos; // 0x6: Current Road Position (addressed as long and word)
   Int2 tilemap_h_target; // 0xA: Tilemap H target
// Stage Lookup Offset - Used to retrieve various data from in-game tables
//
// Stage Map:
//
// 24  23  22  21  20
//   1B  1A  19  18
//     12  11  10
//       09  08
//         00
//
// Increments by 8 each stage.
// Also increments by +1 during the road split section from the values shown above.
//
// 0x38:	Set to -8 during bonus mode section
   Int2 stage_lookup_off;
// These pointers rotate and select the current chunk of road data to blit
   Num2 road_p0; // 0x3A:	Road Pointer 0
   Num2 road_p1; // 0x3C:	Road Pointer 1 (Working road data)
   Num2 road_p2; // 0x3E:	Road Pointer 2 (Chunk of road to be blitted)
   Num2 road_p3; // Ox40:	Road Pointer 3 (Horizon Y Position)
// 0x4C:	Road Width Backup
   Int2 road_width_bak;
// 0x4E:	Car X Backup
   Int2 car_x_bak;
// 0x66:	Road Height Lookup
   Num2 height_lookup;
// 0x722 -	[word] Road Height Index. Working copy of 60066.
   Num2 height_lookup_wrk;
// 0x6C:	Change in road position
   Int4 road_pos_change;
// 0x5E:	Instruct CPU 1 to load end section road. Set Bit 1.
   Num1 road_load_end;
// 0x306:	Road Control
   Num1 road_ctrl;
   enum {
      ROAD_OFF = 0, // Both Roads Off
      ROAD_R0 = 1, // Road 0
      ROAD_R1 = 2, // Road 1
      ROAD_BOTH_P0 = 3, // Both Roads (Road 0 Priority) [DEFAULT]
      ROAD_BOTH_P1 = 4, // Both Roads (Road 1 Priority)
      ROAD_BOTH_P0_INV = 5, // Both Roads (Road 0 Priority) (Road Split. Invert Road 1)
      ROAD_BOTH_P1_INV = 6, // Both Roads (Road 1 Priority) (Road Split. Invert Road 1)
      ROAD_R0_SPLIT = 7, // Road 0 (Road Split.)
      ROAD_R1_SPLIT = 8, // Road 1 (Road Split. Invert Road 1)
   };
// 0x30B:	Road Load Split.
// This should be set to tell CPU 1 to init the road splitting code
//	0    = Do Not Load
//	0xFF = Load
   Int1 road_load_split;
// 0x314:	Road Width
// There are two road generators.
//
// The second road is drawn at an offset from the first, so that it either appears as one solid road, or as two separate roads.
//	00 = 3 lanes
//	D4 = 6 lanes
//
// Once the distance is greater than F0 or so, it's obvious there are two independent roads.
   Int4 road_width; // DANGER! USED AS LONG AND WORD
// 0x420:	Offset Into Road Data [Current Road Position × 4]
// Moved from private for tracked
   Num2 road_data_offset;
#if 0
// 0x4F0:	Start Address of Road Data For Current Stage In ROM
// TODO - move back to being private at some stage
   Num4 stage_addr;
#endif
// 0x510:	Horizon Y Position
   Int2 horizon_y2;
   Int2 horizon_y_bak;
// 0x53C:	Granular Position. More fine than other positioning info. Used to choose road background colour.
   Num2 pos_fine;
// 0x732 -	[long] Base Horizon Y-Offset. Adjusting this almost has the effect of raising the camera.
// Stage 1 is 0x240
// Higher values = higher horizon.
// Note:
// ▪	This is adjusted mid-stage for Stage 2, but remains constant for Stage 1.
   const static Int4 HORIZON_OFF = -0x3FF;
   Int4 horizon_base;
// 0x736:	0 = Base Horizon Value Not Set. 1 = Value Set.
   Num1 horizon_set;
   const static Num2 ARRAY_LENGTH = 0x200;
// 60800 - 60BFF:	Road X-Positions [Before H-Scroll Is Applied] - Same Data For Both Roads
   Int2 road_x[ARRAY_LENGTH];
// 60C00 - 60FFF:	Road 0 H-Scroll Adjusted Positions
   Int2 road0_h[ARRAY_LENGTH];
// 61000 - 613FF:	Road 1 H-Scroll Adjusted Positions
   Int2 road1_h[ARRAY_LENGTH];
// 61400 - 617FF:	Not sure what this is yet
   Int2 road_unk[ARRAY_LENGTH];
// 61800 - 637FF:	Road Y-Positions
//
// Consists of three separate blocks of data:
//	Offset 0x000:	Source Data.
//			List of sequential numbers to indicate when to read next road value from source rom.
//			Numbers iterate down sequentially, until a hill, when they will rise again
//	Offset 0x280:	Priority information for road (during elevated sections). Used to hide sprites
//	Offset 0x400:	Destination Data. Final converted data to be output to road hardware
//
// This format is repeated four times, due to the way values rotate through road ram
   Int2 road_y[0x1000];
   const static Num1 VIEW_ORIGINAL = 0;
   const static Num1 VIEW_ELEVATED = 1;
   const static Num1 VIEW_INCAR = 2;
   ORoad();
   ~ORoad();
   void init();
   void tick();
   Num1 get_view_mode();
   Int2 get_road_y(Num2);
   void set_view_mode(Num1, bool snap = false);
private:
// Enhancement: View Mode
   Num1 view_mode;
// Enhancement: Target Horizon Adjust
   Int2 horizon_target;
// Enhancement: Horizon Offset, used for new view modes
   Int2 horizon_offset;
   Num2 stage_loaded; // 0x4: Current Stage Backup (So we know when to load next stage road data)
   Num4 road_pos_old; // 0x410: Road Position Backup
// 60530 -	[word] Distance into section of track, for height #1
//		Ranges from 0x100 - 0x1FF
   Num2 height_start;
// 0x536 -	[word] Controls switch statement when processing road height
//		0 = Clear Road Height Segment
//		1 = Init Next Road Height Segment
//		2 = Use Elevation
//		3 =
//		4 =
//		5 = Set Base Horizon
   Num2 height_ctrl;
// 0x542:	Granular Position Backup.
   Num2 pos_fine_old;
// 0x544 -	[word] Difference between granular positions.
   Int2 pos_fine_diff;
// 0x70E -	[word] Counter. Counts to 7. Denotes Interpolated track section currently being written.
   Int1 counter;
// 0x710 -	Index Into Height Data (generally specifies hill type for specific section of road)
//		The results of the value will differ depending on which road height section currently on.
//		Not to be confused with 6072A, which is a much larger number.
//		Hack to see different values: wpset 60710, 2, r, 1, {w@60710 = 5; g;}
   Int2 height_index;
// 0x712 -	[long] Final Height Value. Takes Horizon and distance into screen into account.
   Int4 height_final;
// 0x716 -	[word] Increment Value For 0x710 to adjust lookup from height data
   Num2 height_inc;
// 0x718 -	[word] This stores the position into the current road segment we're on.
//		Derived from the granular position and used in conjunction with road height.
//		As a hack try wpset 60718, 2, r, 1, {w@60718 = 0x6b5; g;} you'll stall at a position on the current road segment after value is set.
   Num2 height_step;
// 0x71A -	[word] Jump Table Control For Road Height (Read from Road Data).
   Num2 height_ctrl2;
// 0x71C -	[long] Stores current position into road height data. This is an actual address.
   Num4 height_addr;
// 0x720 -	[word] Elevation Flag
   Int2 elevation;
   enum { DOWN = -1, NO_CHANGE = 0, UP = 1 };
// 0x724 -	[word] Ascend/Descent Hold
   Int2 height_delay;
// 0x726 -	[word] Speed at which to adjust height_step
   Num2 step_adjust;
// 0x728
   Num2 do_height_inc;
// 0x72A -	[word] Distance into section of track, for height #2
//		Ranges from 0x100 - 0x1FF
   Num2 height_end;
// 0x72C:	Up Multiplier
   Int1 up_mult;
// 0x72E:	Down Multiplier
   Int1 down_mult;
// 0x73A:	0 = Base Horizon Value Not Set. 1 = Value Set.
   Num4 horizon_mod;
// 60700:	Lengths of the 7 road segments 60700 - 6070D
   Num2 section_lengths[7];
   Int1 length_offset;
   Num4 a1_lookup;
// Registers - todo: refactor these
   Int4 change_per_entry; // [d2]
   Int4 d5_o;
   Num4 a3_o;
   Num4 y_addr;
   Int2 scanline;
   Int4 total_height;
// Locations in Road RAM
// ─────────────────────
   static const Num4 HW_HSCROLL_TABLE0 = 0x80400;
   static const Num4 HW_HSCROLL_TABLE1 = 0x80800;
   static const Num4 HW_BGCOLOR = 0x80C00;
   void set_default_hscroll();
   void clear_road_ram();
   void init_stage1();
   void do_road();
   void rotate_values();
   void check_load_road();
   void setup_road_x();
   void setup_x_data(Num4);
   void set_tilemap_x(Num4);
   void create_curve(Int2 &, Int2 &, const Int4, const Int4, const Int2, const Int2);
   void setup_hscroll();
   void do_road_offset(Int2 *, Int2, bool);
   void setup_road_y();
   void init_height_seg();
   void init_elevation(Num4 &);
   void do_elevation();
   void init_elevation_delay(Num4 &);
   void do_elevation_delay();
   void init_elevation_mixed(Num4 &);
   void do_elevation_mixed();
   void init_horizon_adjust(Num4 &);
   void do_horizon_adjust();
   void set_road_y();
   void set_y_interpolate();
   void set_y_horizon();
   void set_y_2044();
   void read_next_height();
   void set_elevation();
   void set_horizon_y();
   void do_road_data();
   void blit_roads();
   void blit_road(Num4);
   void output_hscroll(Int2 *, Num4);
   void copy_bg_color();
};
extern ORoad oroad;
