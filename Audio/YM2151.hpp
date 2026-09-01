// Yamaha YM2151 driver (version 2.150 final beta) - May, 11th 2002
//
// (c) 1997-2002 Jarek Burczynski (s0246@poczta.onet.pl, bujar@mame.net)
// Some of the optimizing ideas by Tatsuyuki Satoh
//
// This driver is based upon the MAME source code, with some minor modifications to integrate it into the Cannonball framework.
//
// See http://mamedev.org/source/docs/license.txt for more details.
#pragma once

#include "Types.hpp"
#include "LoadROM.hpp"
#include "Audio/SoundChip.hpp"

// struct describing a single operator
typedef struct {
   Num4 phase; // accumulated operator phase
   Num4 freq; // operator frequency count
   Int4 dt1; // current DT1 (detune 1 phase inc/decrement) value
   Num4 mul; // frequency count multiply
   Num4 dt1_i; // DT1 index × 32
   Num4 dt2; // current DT2 (detune 2) value
   signed int *connects; // operator output 'direction'
// only M1 (operator 0) is filled with this data:
   signed int *mem_connect; // where to put the delayed sample (MEM)
   Int4 mem_value; // delayed sample (MEM) value
// channel specific data; note: each operator number 0 contains channel specific data
   Num4 fb_shift; // feedback shift value for operators 0 in each channel
   Int4 fb_out_curr; // operator feedback value (used only by operators 0)
   Int4 fb_out_prev; // previous feedback value (used only by operators 0)
   Num4 kc; // channel KC (copied to all operators)
   Num4 kc_i; // just for speedup
   Num4 pms; // channel PMS
   Num4 ams; // channel AMS
// end of channel specific data
   Num4 AMmask; // LFO Amplitude Modulation enable mask
   Num4 state; // Envelope state: 4-attack(AR) 3-decay(D1R) 2-sustain(D2R) 1-release(RR) 0-off
   Num1 eg_sh_ar; // (attack state)
   Num1 eg_sel_ar; // (attack state)
   Num4 tl; // Total attenuation Level
   Int4 volume; // current envelope attenuation level
   Num1 eg_sh_d1r; // (decay state)
   Num1 eg_sel_d1r; // (decay state)
   Num4 d1l; // envelope switches to sustain state after reaching this level
   Num1 eg_sh_d2r; // (sustain state)
   Num1 eg_sel_d2r; // (sustain state)
   Num1 eg_sh_rr; // (release state)
   Num1 eg_sel_rr; // (release state)
   Num4 key; // 0=last key was KEY OFF, 1=last key was KEY ON
   Num4 ks; // key scale
   Num4 ar; // attack rate
   Num4 d1r; // decay rate
   Num4 d2r; // sustain rate
   Num4 rr; // release rate
   Num4 reserved0;
   Num4 reserved1;
} YM2151Operator;

class YM2151: public SoundChip {
public:
   bool irq;
   YM2151(float volume, Num4 clock);
   ~YM2151();
   void init(int rate, int fps);
   void stream_update();
   void write_reg(int r, int v);
   int read_status();
private:
   int clock; // chip clock in Hz (passed from 2151intf.c)
   int sampfreq; // sampling frequency in Hz (passed from 2151intf.c)
   float volume;
   void init_tables();
   void init_chip_tables();
   inline void envelope_KONKOFF(YM2151Operator *op, int v);
   inline void set_connect(YM2151Operator *om1, int cha, int v);
   inline void refresh_EG(YM2151Operator *op);
   void ym2151_reset_chip();
   inline signed int op_calc(YM2151Operator *OP, unsigned int env, signed int pm);
   inline signed int op_calc1(YM2151Operator *OP, unsigned int env, signed int pm);
   inline void chan_calc(unsigned int chan);
   inline void chan7_calc();
   inline void advance_eg();
   inline void advance();
};
