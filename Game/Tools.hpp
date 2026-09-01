// OutRun Utility Functions & Assembler Helper Functions.
//
// Common OutRun library functions.
// Helper functions used to facilitate 68K to C++ porting process.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Types.hpp"

class outils {
public:
   static const Num1 DEC_TO_HEX[];
   outils();
   ~outils();
   static void reset_random_seed();
   static Num4 random();
   static Int4 isqrt(Int4);
   static Num2 convert16_dechex(Num2);
   static Num4 bcd_add(Num4, Num4);
   static Num4 bcd_sub(Num4, Num4);
// Inline functions
   inline static void move16(Num4 src, Num4 &dst) {
      dst = (dst&0xFFFF0000) + (src&0xFFFF);
   }
   inline static void add16(Num4 src, Num4 &dst) {
      dst = (dst&0xFFFF0000) + (((dst&0xFFFF) + (src&0xFFFF))&0xFFFF);
   }
   inline static void sub16(Int4 src, Int4 &dst) {
      dst = (dst&0xFFFF0000) + (((dst&0xFFFF) - (src&0xFFFF))&0xFFFF);
   }
   inline static void swap32(Int4 &v) {
      v = ((v&0xFFFF0000) >> 16) + ((v&0xFFFF) << 16);
   }
   inline static void swap32(Num4 &v) {
      v = ((v&0xFFFF0000) >> 16) + ((v&0xFFFF) << 16);
   }
   static void convert_counter_to_time(Num2 counter, Num1 *converted);
private:
   static Int4 next(Int4, Int4);
   static Int4 abs(Int4);
};
