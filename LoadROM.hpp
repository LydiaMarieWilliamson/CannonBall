// Binary File Loader.
//
// Handles loading an individual binary file to memory.
// Supports reading bytes, words and longs from this area of memory.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

class RomLoader {
public:
   enum { NORMAL = 1, INTERLEAVE2 = 2, INTERLEAVE4 = 4 };
   Num1 *rom;
// Size of rom
   Num4 length;
// Successfully loaded
   bool loaded;
   RomLoader();
   ~RomLoader();
   void init(Num4);
   int (RomLoader::*load)(const char *, const int, const int, const int, const Num1, const bool);
   int load_rom(const char *filename, const int offset, const int length, const int expected_crc, const Num1 mode = NORMAL, const bool verbose = true);
   int load_crc32(const char *debug, const int offset, const int length, const int expected_crc, const Num1 mode = NORMAL, const bool verbose = true);
   int load_binary(const char *filename);
   void unload(void);
// Used by translated 68000 Code
// ─────────────────────────────
   inline Num4 read32(Num4 *addr) {
      Num4 data = (rom[*addr] << 24) | (rom[*addr + 1] << 16) | (rom[*addr + 2] << 8) | (rom[*addr + 3]);
      *addr += 4;
      return data;
   }
   inline Num2 read16(Num4 *addr) {
      Num2 data = (rom[*addr] << 8) | (rom[*addr + 1]);
      *addr += 2;
      return data;
   }
   inline Num1 read8(Num4 *addr) {
      return rom[(*addr)++];
   }
   inline Num4 read32(Num4 addr) {
      return (rom[addr] << 24) | (rom[addr + 1] << 16) | (rom[addr + 2] << 8) | rom[addr + 3];
   }
   inline Num2 read16(Num4 addr) {
      return (rom[addr] << 8) | rom[addr + 1];
   }
   inline Num1 read8(Num4 addr) {
      return rom[addr];
   }
// Used by translated Z80 Code
// ───────────────────────────
// Note that the endian is reversed compared with the 68000 code.
   inline Num2 read16(Num2 *addr) {
      Num2 data = (rom[*addr + 1] << 8) | (rom[*addr]);
      *addr += 2;
      return data;
   }
   inline Num1 read8(Num2 *addr) {
      return rom[(*addr)++];
   }
   inline Num2 read16(Num2 addr) {
      return (rom[addr + 1] << 8) | rom[addr];
   }
   inline Num1 read8(Num2 addr) {
      return rom[addr];
   }
private:
   int create_map();
   int filesize(const char *filename);
};
