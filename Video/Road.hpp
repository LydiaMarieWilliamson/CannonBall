#pragma once

#include "Types.hpp"

class HWRoad {
public:
   HWRoad();
   ~HWRoad();
   void init(const Num1 *, const bool hires);
   void write16(Num4 adr, const Num2 data);
   void write16(Num4 *adr, const Num2 data);
   void write32(Num4 *adr, const Num4 data);
   Num2 read_road_control();
   void write_road_control(const Num1);
   void (HWRoad::*render_background)(Num2 *);
   void (HWRoad::*render_foreground)(Num2 *);
private:
   Num1 road_control;
   Num2 color_offset1;
   Num2 color_offset2;
   Num2 color_offset3;
   Int4 x_offset;
   static const Num2 ROAD_RAM_SIZE = 0x1000;
   static const Num2 rom_size = 0x8000;
// Decoded road graphics
   Num1 roads[0x40200];
// Two halves of RAM
   Num2 ram[ROAD_RAM_SIZE/2];
   Num2 ramBuff[ROAD_RAM_SIZE/2];
   void decode_road(const Num1 *);
   void render_background_lores(Num2 *);
   void render_foreground_lores(Num2 *);
   void render_background_hires(Num2 *);
   void render_foreground_hires(Num2 *);
};
extern HWRoad hwroad;
