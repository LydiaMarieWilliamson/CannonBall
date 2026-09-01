// Sound Chip
//
// This is an abstract class, used by the Sega PCM and YM2151 chips.
// It facilitates writing to a buffer of sound data.
//
// Copyright Chris White.
// See License.txt for more details.
#include "Types.hpp"
#include "Audio/SoundChip.hpp"

SoundChip::SoundChip() {
   volume = 1.0;
   initalized = false;
}

SoundChip::~SoundChip() {
   delete[]buffer;
}

void SoundChip::init(Num1 channels, Int4 sample_freq, Int4 fps) {
   this->fps = fps;
   this->sample_freq = sample_freq;
   this->channels = channels;
   frame_size = sample_freq/fps;
   buffer_size = frame_size*channels;
   if (initalized)
      delete[]buffer;
   buffer = new Int2[buffer_size];
   initalized = true;
}

// Set soundchip volume (0 = Off, 10 = Loudest)
void SoundChip::set_volume(Num1 v) {
   if (v > 10)
      return;
   volume = (float)(v/10.0);
}

void SoundChip::clear_buffer() {
   for (Num4 i = 0; i < buffer_size; i++)
      buffer[i] = 0;
}

void SoundChip::write_buffer(const Num1 channel, Num4 address, Int2 value) {
#if 0
   buffer[channel + (address*channels)] = (Int2)(value*volume); // Unused for now
#else
   buffer[channel + (address*channels)] = value;
#endif
}

Int2 SoundChip::read_buffer(const Num1 channel, Num4 address) {
   return buffer[channel + (address*channels)];
}

Int2 *SoundChip::get_buffer() {
   return buffer;
}
