// Interface to Ported Z80 Code.
// Handles the interface between 68000 program code and Z80.
//
// Also abstracted here, so the more complex OSound class isn't exposed to the main code directly
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Audio/SegaPCM.hpp"
#include "Audio/YM2151.hpp"
#include "Game/Sound/Commands.hpp"

class OSoundInt {
public:
// SoundChip: Sega Custom Sample Generator
   SegaPCM *pcm;
// SoundChip: Yamaha YM2151
   YM2151 *ym;
   const static Num2 PCM_RAM_SIZE = 0x100;
// Note whether the game has booted
   bool has_booted;
// [+0] Unused
// [+1] Engine pitch high
// [+2] Engine pitch low
// [+3] Engine pitch vol
// [+4] Traffic data #1
// [+5] Traffic data #2
// [+6] Traffic data #3
// [+7] Traffic data #4
   Num1 engine_data[8];
   OSoundInt();
   ~OSoundInt();
   void init();
   void reset();
   void tick();
   void play_queued_sound();
   void queue_sound_service(Num1 snd);
   void queue_sound(Num1 snd);
   void queue_clear();
private:
// 4 MHz
   static const Num4 SOUND_CLOCK = 4000000;
// Fractionally counts number of times audio code must be called
// We call the audio code 125 times per frame from a timing perspective.
   double audio_ticks;
// Reference to 0xFF bytes of PCM Chip RAM
   Num1 *pcm_ram;
// Controls what type of sound we're going to process in the interrupt routine
   Num1 sound_counter;
   static const Num1 QUEUE_LENGTH = 0x1F;
   Num1 queue[QUEUE_LENGTH + 1];
// Number of sounds queued
   Num1 sounds_queued;
// Positions in the queue
   Num1 sound_head, sound_tail;
   void add_to_queue(Num1 snd);
};
extern OSoundInt osoundint;
