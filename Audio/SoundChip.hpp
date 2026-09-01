// Sound Chip
//
// This is an abstract class, used by the Sega PCM and YM2151 chips.
// It facilitates writing to a buffer of sound data.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

class SoundChip {
public:
   bool initalized;
// Sample Frequency in use
   Num4 sample_freq;
// How many channels to support (mono/stereo)
   Num1 channels;
// Size of the buffer (including channel info)
   Num4 buffer_size;
   SoundChip();
   ~SoundChip();
   void init(Num1, Int4, Int4);
// Pure virtual function. Denotes virtual class.
   virtual void stream_update() = 0;
   Int2 *get_buffer();
   void set_volume(Num1);
protected:
   const static Num1 MONO = 1;
   const static Num1 STEREO = 2;
   const static Num1 LEFT = 0;
   const static Num1 RIGHT = 1;
// Buffer size for one frame (excluding channel info)
   Num4 frame_size;
// Volume of sound chip
   float volume;
   void clear_buffer();
   void write_buffer(const Num1, Num4, Int2);
   Int2 read_buffer(const Num1, Num4);
private:
// Sound buffer stream
   Int2 *buffer;
// Frames per second
   Num4 fps;
};
