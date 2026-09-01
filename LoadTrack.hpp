// Track Loading Code.
//
// Abstracts the level format, so that the original ROMs as well as in conjunction with track data from the LayOut editor.
// -	Handles levels (path, width, height, scenery)
// -	Handles additional level sections (road split, end section)
// -	Handles road/level related palettes
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "Globals.hpp"

// Road Generator Palette Representation
struct RoadPalette {
   Num4 stripe_centre; // Centre Stripe Colour
   Num4 stripe; // Stripe Colour
   Num4 side; // Side Colour
   Num4 road; // Main Road Colour
};

// OutRun Level Representation
struct Level {
   Num1 *path; // CPU 1 Path Data
   Num1 *curve; // Track Curve Information (Derived From Path)
   Num1 *width_height; // Track Width & Height Lookups
   Num1 *scenery; // Track Scenery Lookups
   Num2 pal_sky; // Index into Sky Palettes
   Num2 pal_gnd; // Index into Ground Palettes
   RoadPalette palr1; // Road 1 Generator Palette
   RoadPalette palr2; // Road 2 Generator Palette
};

// LayOut Binary Header Format
struct LayOut {
   static const Num4 EXPECTED_VERSION = 1;
   static const Num4 HEADER = 0;
   static const Num4 PATH = HEADER + sizeof(Num4) + sizeof(Num1);
   static const Num4 LEVELS = PATH + sizeof(Num4);
   static const Num4 END_PATH = LEVELS + (STAGES*sizeof(Num4));
   static const Num4 END_LEVELS = END_PATH + sizeof(Num4);
   static const Num4 SPLIT_PATH = END_LEVELS + (5*sizeof(Num4));
   static const Num4 SPLIT_LEVEL = SPLIT_PATH + sizeof(Num4);
   static const Num4 PAL_SKY = SPLIT_LEVEL + sizeof(Num4);
   static const Num4 PAL_GND = PAL_SKY + sizeof(Num4);
   static const Num4 SPRITE_MAPS = PAL_GND + sizeof(Num4);
   static const Num4 HEIGHT_MAPS = SPRITE_MAPS + sizeof(Num4);
};

class RomLoader;

class TrackLoader {
public:
// Reference to stage mapping/ordering table
   Num1 *stage_data;
   Level *current_level;
   const static int MODE_ORIGINAL = 0;
   const static int MODE_LAYOUT = 1;
// Display start line on Stage 1
   Num1 display_start_line;
   Num4 curve_offset;
   Num4 wh_offset;
   Num4 scenery_offset;
// Shared Structures
   Num1 *pal_sky_data;
   Num1 *pal_gnd_data;
   Num1 *heightmap_data;
   Num1 *scenerymap_data;
   Num4 pal_sky_offset;
   Num4 pal_gnd_offset;
   Num4 heightmap_offset;
   Num4 scenerymap_offset;
   TrackLoader();
   ~TrackLoader();
   void init(bool jap);
   bool set_layout_track(const char *filename);
   void init_original_tracks(bool jap);
   void init_layout_tracks(bool jap);
   void init_track(const Num4);
   void init_track_split();
   void init_track_bonus(const Num4);
   void init_path(const Num4);
   void init_path_split();
   void init_path_end();
   Num4 read_pal_sky_table(Num2 entry);
   Num4 read_pal_gnd_table(Num2 entry);
   Num4 read_heightmap_table(Num2 entry);
   Num4 read_scenerymap_table(Num2 entry);
   Int2 readPath(Num4 addr);
   Int2 readPath(Num4 *addr);
   Int2 read_width_height(Num4 *addr);
   Int2 read_curve(Num4 addr);
   Num2 read_scenery_pos();
   Num1 read_total_sprites();
   Num1 read_sprite_pattern_index();
   Int1 stage_offset_to_level(Num4);
   Level *get_level(Num4);
   inline Int4 read32(Num1 *data, Num4 *addr) {
      Int4 value = (data[*addr] << 24) | (data[*addr + 1] << 16) | (data[*addr + 2] << 8) | (data[*addr + 3]);
      *addr += 4;
      return value;
   }
   inline Int2 read16(Num1 *data, Num4 *addr) {
      Int2 value = (data[*addr] << 8) | (data[*addr + 1]);
      *addr += 2;
      return value;
   }
   inline Int1 read8(Num1 *data, Num4 *addr) {
      return data[(*addr)++];
   }
   inline Int4 read32(Num1 *data, Num4 addr) {
      return (data[addr] << 24) | (data[addr + 1] << 16) | (data[addr + 2] << 8) | data[addr + 3];
   }
   inline Int2 read16(Num1 *data, Num4 addr) {
      return (data[addr] << 8) | data[addr + 1];
   }
   inline Int1 read8(Num1 *data, Num4 addr) {
      return data[addr];
   }
private:
   RomLoader *layout;
   int mode;
   Level *levels; // Normal Stages
   Level *level_split; // Split Section
   Level *levels_end; // End Section
   Num1 *current_path; // CPU 1 Road Path
   void setup_level(Level *l, RomLoader *data, const int STAGE_ADR);
   void setup_section(Level *l, RomLoader *data, const int STAGE_ADR);
};
extern TrackLoader trackloader;
