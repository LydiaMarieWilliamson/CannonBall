// Smoke & Spray Control.
//
// Animate the smoke and spray below the Ferrari's wheels.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Game/OutRun.hpp"

class OSmoke {
public:
// Load smoke sprites for next level?
   Int1 load_smoke_data;
   OSmoke(void);
   ~OSmoke(void);
   void init();
   void setup_smoke_sprite(bool);
   void draw_ferrari_smoke(oentry *);
   void draw(oentry *);
private:
// Ferrari wheel smoke type on road
   Num2 smoke_type_onroad;
// Ferrari wheel smoke type off road
   Num2 smoke_type_offroad;
// Ferrari wheel smoke type after car collision
   Num2 smoke_type_slip;
   void tick_smoke_anim(oentry *, Int1, Num4);
};
extern OSmoke osmoke;
