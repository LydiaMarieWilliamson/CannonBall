// Level Object Logic
//
// This class handles rendering most of the objects that comprise a typical level.
// -	Configures rendering properties (co-ordinates, zoom etc.)
// -	Object specific logic, including collision checks & start lights etc.
//
// The original codebase contains a large amount of code duplication, much of which is duplicated here.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Game/OutRun.hpp"

class OLevelObjs {
public:
// Spray Counter (Going Through Water).
   Num2 spray_counter;
// Wheel Spray Type
//	00 = Water
//	04 = Yellow Stuff
//	08 = Green Stuff
//	0c = Pink stuff
//	10 = Smoke
   Num2 spray_type;
// Collision With Sprite Has Ocurred
//	0 = No Collision
//	1 = Collision (and increments for every additional collision in this crash cycle)
   Num1 collision_sprite;
// Sprite Collision Counter (Hitting Scenery)
   Int2 sprite_collision_counter;
   OLevelObjs(void);
   ~OLevelObjs(void);
   void init_startline_sprites();
   void init_timetrial_sprites();
   void init_hiscore_sprites();
   void setup_sprites(Num4);
   void do_sprite_routine();
   void hide_sprite(oentry *);
private:
// Default sprite entries for stage 1 initialization
   const static Num1 DEF_SPRITE_ENTRIES = 0x44;
// Hi-Score Sprite Entries
   const static Num1 HISCORE_SPRITE_ENTRIES = 0x40;
   const static Num1 COLLISION_RESET = 4;
   const static Num2 SPRAY_RESET = 0xC;
   void init_entries(Num4, const Num1 start_index, const Num1);
   void setup_sprite(oentry *, Num4);
   void setup_sprite_routine(oentry *);
   void sprite_collision_z1c(oentry *);
   void sprite_lights(oentry *);
   void sprite_lights_countdown(oentry *);
   void sprite_grass(oentry *sprite);
   void sprite_water(oentry *sprite);
   void sprite_rocks(oentry *sprite);
   void sprite_debris(oentry *sprite);
   void sprite_minitree(oentry *sprite);
   void do_thickness_sprite(oentry *sprite, const Num4);
   void sprite_clouds(oentry *sprite);
   void sprite_normal(oentry *, Num1);
   void set_spr_zoom_priority(oentry *, Num1);
   void set_spr_zoom_priority2(oentry *, Num1);
   void set_spr_zoom_priority_rocks(oentry *, Num1);
};
extern OLevelObjs olevelobjs;
