#pragma once

#include "Types.hpp"

class video;

class hwsprites {
public:
   hwsprites();
   ~hwsprites();
   void init(const Num1 *);
   void reset();
   void set_x_clip(bool);
   void swap();
   Num1 read(const Num2 adr);
   void write(const Num2 adr, const Num2 data);
   void render(const Num1);
private:
// Clip values.
   Num2 x1, x2;
// 128 sprites, 16 bytes each (0x400)
   static const Num2 SPRITE_RAM_SIZE = 128*8;
   static const Num4 SPRITES_LENGTH = 0x100000 >> 2;
   static const Num2 COLOR_BASE = 0x800;
   Num4 sprites[SPRITES_LENGTH]; // Converted sprites
// Two halves of RAM
   Num2 ram[SPRITE_RAM_SIZE];
   Num2 ramBuff[SPRITE_RAM_SIZE];
};
