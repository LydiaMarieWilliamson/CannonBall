// Sega 8-Bit PCM Driver
//
// This driver is based upon the MAME source code, with some minor modifications to integrate it into the Cannonball framework.
//
// Note, that I've altered this driver to output at a fixed 44100 Hz.
// This is to avoid the need for downsampling.
//
// See http://mamedev.org/source/docs/license.txt for more details.
#pragma once

#include "Types.hpp"
#include "LoadROM.hpp"
#include "Audio/SoundChip.hpp"

class SegaPCM: public SoundChip {
public:
   static const Num4 BANK_256 = (11);
   static const Num4 BANK_512 = (12);
   static const Num4 BANK_12M = (13);
   static const Num4 BANK_MASK7 = (0x70 << 16);
   static const Num4 BANK_MASKF = (0xf0 << 16);
   static const Num4 BANK_MASKF8 = (0xf8 << 16);
   SegaPCM(Num4 clock, RomLoader *rom, Num1 *ram, Int4 bank);
   ~SegaPCM();
   void init(Int4 rate, Int4 fps);
   void stream_update();
private:
// PCM Chip Emulation
   Num1 *ram;
   Num1 *low;
   Num1 *pcm_rom;
   Int4 max_addr;
   Int4 bankshift;
   Int4 bankmask;
   Int4 rgnmask;
   double downsample;
};
