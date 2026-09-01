// Tilemap Handling Code.
//
// Logic for the foreground and background tilemap layers.
// -	Read and render tilemaps
// -	H-Scroll & V-Scroll
// -	Palette Initialization
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include "OutRun.hpp"

// Forward definition of video for cyclic dependency
class video;

class OTiles {
public:
// + 0x21: Tilemap Control
//	0 = Clear Tile Table 1 & Init Default Tilemap (Stage 1)
//	1 = Scroll Tilemap
//	2 = Init Tilemap
//	3 = New Tilemap Initialized - Scroll both tilemaps during tilesplit
   Num1 tilemap_ctrl;
   enum { TILEMAP_CLEAR, TILEMAP_SCROLL, TILEMAP_INIT, TILEMAP_SPLIT };
   OTiles();
   ~OTiles();
   void init();
   void set_vertical_swap();
   void setup_palette_tilemap();
   void setup_palette_widescreen();
   void setup_palette_hud();
   void reset_tiles_pal();
   void update_tilemaps(Int1);
   void init_tilemap_palette(Num2);
   void fill_tilemap_color(Num2);
   void write_tilemap_hw();
   void set_scroll(Int2 h_scroll = 0, Int2 v_scroll = 0);
private:
// Page to use for tilemap.
// Alternates between 0 and 1 dependent on stage number to handle switch between tilemaps at stage end.
   Int1 page;
// Enhancement: Used for continuous mode
   Int2 vswap_state;
   enum { VSWAP_OFF, VSWAP_SCROLL_OFF, VSWAP_SCROLL_ON };
   Int2 vswap_off;
// TILEMAP VARIABLES
// ─────────────────
// Scroll values to write to foreground & background tilemaps
   Int2 fg_h_scroll;
   Int2 bg_h_scroll;
   Int2 fg_v_scroll;
   Int2 bg_v_scroll;
   Num2 fg_psel;
   Num2 bg_psel;
// + 0x0C:	Current master tilemap scroll values
   Int2 tilemap_v_scr;
   Int4 tilemap_h_scr;
// BG & FG Tilemap Height in Tiles
   Num2 fg_v_tiles;
   Num2 bg_v_tiles;
// + 0x16:	Tilemap v-scroll offset. Generally static.
   Int2 tilemap_v_off;
// FG & BG Tilemap ROM Address [long]
   Num4 fg_addr;
   Num4 bg_addr;
// + 0x20:	Toggle between loading palette and loading tiles
   Num1 tilemap_setup;
   enum { SETUP_TILES, SETUP_PAL };
// + 0x22:	Clear Old Name Tables
   bool clear_name_tables;
// + 0x23:	Set when road is splitting (used by UpdateFGPage and UpdateBGPage)
   bool page_split;
// + 0x24:	H-Scroll Lookup Table
   Num2 h_scroll_lookup;
   void clear_tile_info();
   void init_tilemap(Int2 stage_id = 0);
   void init_tilemap_props(Num2);
   void scroll_tilemaps();
   void init_next_tilemap();
   void copy_to_palram(const Num1, Num4, Num4);
   void split_tilemaps();
   void loop_to_stage1();
   void clear_old_name_table();
   void h_scroll_tilemaps();
   void v_scroll_tilemaps();
   void copy_fg_tiles(Num4);
   void copy_bg_tiles(Num4);
   void update_fg_page();
   void update_bg_page();
   void update_fg_page_split();
   void update_bg_page_split();
};
extern OTiles otiles;
