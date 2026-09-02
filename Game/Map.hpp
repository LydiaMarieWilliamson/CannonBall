// Course Map Logic & Rendering.
//
// This is the full-screen map that is displayed at the end of the game.
//
// The logo is built from multiple sprite components.
//
// The course map itself is made up of sprites and pieced together.
// It's not a tilemap.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Game/OutRun.hpp"

class OMap {
public:
// Load Sprites Needed for Course Map
   bool init_sprites;
   OMap(void);
   ~OMap(void);
   void init();
   void tick();
   void blit();
   void load_sprites();
   void draw_course_map();
   void position_ferrari(Num1 index);
private:
// Total sprite pieces that comprise course map. 3c
   const static Num1 MAP_PIECES = 0x3C;
   Num1 map_state;
   enum {
      MAP_INIT = 0,
   // Do Route [Note map is displayed from this point on]
      MAP_ROUTE = 0x4,
   // Do Final Segment Of Route [Car still moving]
      MAP_ROUTE_FINAL = 0x08,
   // Route Concluded
      MAP_ROUTE_DONE = 0x0C,
   // Init Delay Counter For Map Display
      MAP_INIT_DELAY = 0x10,
   // Display Map
      MAP_DISPLAY = 0x14,
   // Clear Course Map
      MAP_CLEAR = 0x18,
   };
// Direction to move on mini-map
//	Bit 0:	0 = Up   (Left Route)
//		1 = Down (Right Route)
   Num1 map_route;
// Minimap Position (Per Segment Basis)
   Int2 map_pos;
// Minimap Position (Final Segment)
   Int2 map_pos_final;
// Map Delay Counter
   Int2 map_delay;
// Stage counter for course map screen. [Increments]
   Int2 map_stage1;
// Stage counter for course map screen. [Decrements]
// Loaded with stage, then counts down as course map logic runs.
   Int2 map_stage2;
// Minicar Movement Enabled (set = enabled)
   Num1 minicar_enable;
   void draw_horiz_end(oentry *);
   void draw_vert_bottom(oentry *);
   void draw_vert_top(oentry *);
   void draw_piece(oentry *, Num4);
   void do_route_final();
   void end_route();
   void init_map_delay();
   void map_display();
   void move_mini_car(oentry *);
};
extern OMap omap;
