// Hardware Sprites.
//
// This class stores sprites in the converted format expected by the
// OutRun graphics hardware.
//
// Copyright Chris White.
// See License.txt for more details.
#include "Types.hpp"

class osprite {
public:
   Num2 data[0x7];
   Num4 scratch;
   osprite(void);
   ~osprite(void);
   void init();
   Num2 get_x();
   Num2 get_y();
   void set_x(Num2);
   void inc_x(Num2);
   void set_y(Num2);
   void set_pitch(Num1);
   void set_vzoom(Num2);
   void set_hzoom(Num2);
   void set_priority(Num1);
   void set_offset(Num2 o);
   void inc_offset(Num2 o);
   void set_render(Num1 b);
   void set_pal(Num1);
   void set_height(Num1);
   void sub_height(Num1);
   void set_bank(Num1);
   void hide();
private:
};
