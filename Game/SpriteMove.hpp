// Animated Sprites.
//
// This format is essentially a deviation from the normal sprites used in the game.
//
// Some of the entries in the block of memory are replaced and used for other purposes, which can be seen below.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Game/SpriteEntry.hpp"

class oanimsprite {
public:
// Base Sprite
   oentry *sprite;
// +0x06 [Byte]	Sprite/Object Index Being Processed
//		1 = Car Door
//		2 = Ferrari Interior
//		3 = Car Shadow
//		4 = Man Sprite
//		5 = Man Shadow
//		6 = Female Sprite
//		7 = Female Shadow
//		8 = Trophy Person
//		9 = Trophy Shadow
//		A = After Effects (e.g. smoke cloud on genie animation)
// +0x1E [Long]	Reference to the CURRENT block of animation data.
   Num4 anim_addr_curr;
// +0x22 [Long]	Reference to the NEXT block of animation data.
   Num4 anim_addr_next;
// +0x26 [Word]	Animation Frame Number
   Int2 anim_frame;
// +0x28 [Word]	Frame Delay (Before increment to next frame)
   Num1 frame_delay;
// +0x2A [Word]	Increment End Sequence Position When Set
   Num2 anim_props;
// +0x2C [Word]	Animation State
   Int2 anim_state;
   void init(oentry *s) {
      sprite = s;
      sprite->function_holder = -1;
      anim_addr_curr = 0;
      anim_addr_next = 0;
      anim_frame = 0;
      frame_delay = 0;
      anim_props = 0;
      anim_state = 0;
   }
};
