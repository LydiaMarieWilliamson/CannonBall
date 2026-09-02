// Process Inputs.
// -	Read & Process inputs and controls.
// -	Note, this class does not contain platform specific code.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Play/Input.hpp"
#include "Game/OutRun.hpp"

class OInputs {
public:
   const static Num1 BRAKE_THRESHOLD1 = 0x80;
   const static Num1 BRAKE_THRESHOLD2 = 0xA0;
   const static Num1 BRAKE_THRESHOLD3 = 0xC0;
   const static Num1 BRAKE_THRESHOLD4 = 0xE0;
   Int1 crash_input;
// Acceleration Input
   Int2 input_acc;
// Steering Input
   Int2 input_steering;
// Processed / Adjusted Values
   Int2 steering_adjust;
   Int2 acc_adjust;
   Int2 brake_adjust;
// True = High Gear. False = Low Gear.
   bool gear;
   OInputs(void);
   ~OInputs(void);
   void init();
   void tick();
   void adjust_inputs();
   void do_gear();
   Num1 do_credits();
   bool is_analog_l();
   bool is_analog_r();
   bool is_analog_select();
private:
// Variables for port
// ──────────────────
// Amount to adjust steering per tick. (0x3 is a good test value)
   Num1 steering_inc;
// Amount to adjust acceleration per tick. (0x10 is a good test value)
   Num1 acc_inc;
// Amount to adjust brake per tick. (0x10 is a good test value)
   Num1 brake_inc;
   static const int DELAY_RESET = 40;
   int delay1, delay2, delay3;
// Coin Inputs (Only used by CannonBoard)
   bool coin1, coin2;
// Variables from original code
// ────────────────────────────
   const static Num1 STEERING_MIN = 0x48;
   const static Num1 STEERING_MAX = 0xB8;
   const static Num1 STEERING_CENTRE = 0x80;
// Current steering value
   Int2 steering_old;
   Int2 steering_change;
   const static Num1 PEDAL_MIN = 0x30;
   const static Num1 PEDAL_MAX = 0x90;
// Brake Input
   Int2 input_brake;
   void digital_steering();
   void digital_pedals();
};
extern OInputs oinputs;
