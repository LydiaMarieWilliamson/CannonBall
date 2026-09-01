// Cabinet Diagnostics.
//
// Diagnostics Modes. Based On Original Code, with modifications.
// Mostly of use for real cabinets.
// -	CRT Check
// -	SMARTYPI Interface Check
// -	Motor Hardware Test
// -	Brake/Start Lamp Test
// -	Control Input Test
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "../Types.hpp"

class CabDiag {
public:
   enum {
      STATE_CRT,
      STATE_INPUT,
      STATE_OUTPUT,
      STATE_MOTORT,
   };
   CabDiag();
   ~CabDiag(void);
   bool tick();
   void set(Num1);
private:
   bool init;
   bool done;
   Num1 state;
   Num1 counter;
// Can user press start to exit mode?
   bool press_start_to_exit;
   void reset();
   void init_output();
   void tick_output();
   void init_input();
   void tick_input();
   void init_crt();
   void blit_box();
   void blit1_block(Num4 adr, Num4 data);
   void blit7_block(Num4 *adr, Num4 data);
   void init_motor_test();
   void tick_motor();
};
