// Process Outputs.
// -	Only the Deluxe Moving Motor Code is ported for now.
// -	This is used by the force-feedback haptic system.
//
// One thing to note is that this code was originally intended to drive a moving hydraulic cabinet, not to be mapped to a haptic device.
//
// Therefore, it's not perfect when used in this way, but the results aren't bad :)
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Types.hpp"

struct CoinChute {
// Coin Chute Counters
   Num1 counter[3];
// Output bit
   Num1 output_bit;
};

class OOutputs {
public:
   const static int MODE_DISABLED = 0; // Disabled
   const static int MODE_CABINET = 1; // SmartyPi Interface / Original Cabinet
   const static int MODE_FFEEDBACK = 2; // Force Feedback for Wheels
   const static int MODE_RUMBLE = 3; // Simple rumble for controllers
// Hardware Motor Control:
//	0 = Switch off
//	5 = Left
//	8 = Centre
//	B = Right
   Num1 hw_motor_control, hw_motor_control_old;
// Digital Outputs
   enum {
      D_EXT_MUTE = 0x01, // bit 0 = External Amplifier Mute Control
      D_BRAKE_LAMP = 0x02, // bit 1 = brake lamp
      D_START_LAMP = 0x04, // bit 2 = start lamp
      D_COIN1_SUCC = 0x08, // bit 3 = Coin successfully inserted - Chute 2
      D_COIN2_SUCC = 0x10, // bit 4 = Coin successfully inserted - Chute 1
      D_MOTOR = 0x20, // bit 5 = steering wheel central vibration
      D_UNUSED = 0x40, // bit 6 = ?
      D_SOUND = 0x80, // bit 7 = sound enable
   };
   CoinChute chute1, chute2;
   OOutputs(void);
   ~OOutputs(void);
   void init();
   void set_mode(int);
   bool diag_motor(Int2 input_motor, Num1 hw_motor_limit);
   bool calibrate_motor(Int2 input_motor, Num1 hw_motor_limit);
   void tick(Int2 input_motor = 0);
   void writeDigitalToConsole();
   void set_digital(Num1);
   void clear_digital(Num1);
   int is_set(Num1);
   void coin_chute_out(CoinChute *chute, bool insert);
private:
   int mode;
   Num1 dig_out, dig_out_old;
   const static Num2 STATE_INIT = 0;
   const static Num2 STATE_DELAY = 1;
   const static Num2 STATE_LEFT = 2;
   const static Num2 STATE_RIGHT = 3;
   const static Num2 STATE_CENTRE = 4;
   const static Num2 STATE_DONE = 5;
   const static Num2 STATE_EXIT = 6;
// Calibration Counter
   const static int COUNTER_RESET = 300;
   const static Num1 MOTOR_OFF = 0;
   const static Num1 MOTOR_RIGHT = 0x5;
   const static Num1 MOTOR_CENTRE = 0x8;
   const static Num1 MOTOR_LEFT = 0xB;
// These are calculated during startup in the original game.
// Here we just hardcode them, as the motor init code isn't ported.
   const static Num1 CENTRE_POS = 0x80;
   const static Num1 LEFT_LIMIT = 0xC1;
   const static Num1 RIGHT_LIMIT = 0x3C;
// Motor Limit Values. Calibrated during startup.
   Int2 limit_left;
   Int2 limit_right;
// Motor Centre Position. (We Fudge this for Force Feedback wheel mode.)
   Int2 motor_centre_pos;
// Difference between input_motor and input_motor_old
   Int2 motor_x_change;
   Num2 motor_state;
   bool motor_enabled;
// 0x11: Motor Control Value
   Int1 motor_control;
// 0x12: Movement (1 = Left, -1 = Right, 0 = None)
   Int1 motor_movement;
// 0x14: Is Motor Centered
   bool is_centered;
// 0x16: Motor X Change Latch
   Int2 motor_change_latch;
// 0x18: Speed
   Int2 speed;
// 0x1A: Road Curve
   Int2 curve;
// 0x1E: Increment counter to index motor table for off-road/crash
   Int2 vibrate_counter;
// 0x20: Last Motor X_Change > 8. No need to adjust further.
   bool was_small_change;
// 0x22: Adjusted movement value based on steering 1
   Int2 movement_adjust1;
// 0x24: Adjusted movement value based on steering 2
   Int2 movement_adjust2;
// 0x26: Adjusted movement value based on steering 3
   Int2 movement_adjust3;
// Counter control for motor tests
   Int2 counter;
// Columns for output
   Num2 col1, col2;
   void diag_left(Int2 input_motor, Num1 hw_motor_limit);
   void diag_right(Int2 input_motor, Num1 hw_motor_limit);
   void diag_centre(Int2 input_motor, Num1 hw_motor_limit);
   void diag_done();
   void calibrate_left(Int2 input_motor, Num1 hw_motor_limit);
   void calibrate_right(Int2 input_motor, Num1 hw_motor_limit);
   void calibrate_centre(Int2 input_motor, Num1 hw_motor_limit);
   void calibrate_done();
   void do_motors(const int MODE, Int2 input_motor);
   void car_moving(const int MODE);
   void car_stationary();
   void adjust_motor();
   void do_motor_crash();
   void do_motor_offroad();
   void set_value(const Num1 *, Num1);
   void done();
   void motor_output(Num1 cmd);
   void do_vibrate_upright();
   void do_vibrate_mini();
};
