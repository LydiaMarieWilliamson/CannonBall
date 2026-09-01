// Data Types.
// An abstraction layer for <stdint.h> and Windows Visual Studio.
// Exports: IntN for signed integer types, NumN for unsigned integer types strictly of sizes N ∈ {1, 2, 4, 8} bytes.
//
// The Boost library is only used to enforce data type size at compile time.
//
// If you're sure the sizes are correct, it can be removed for your port.
//
// Copyright Chris White.
// See License.txt for more details.
#pragma once

#include <boost/static_assert.hpp>

// C99 Standard Naming
#if defined _MSC_VER
typedef signed char Int1;
typedef signed short Int2;
typedef signed int Int4;
typedef signed long long Int8;
typedef unsigned char Num1;
typedef unsigned short Num2;
typedef unsigned int Num4;
typedef unsigned long long Num8;
#else
#   include <stdint.h>
typedef int8_t Int1;
typedef int16_t Int2;
typedef int32_t Int4;
typedef int64_t Int8;
typedef uint8_t Num1;
typedef uint16_t Num2;
typedef uint32_t Num4;
typedef uint64_t Num8;
#endif

// Report typedef errors: enforce type-size restrictions.
BOOST_STATIC_ASSERT_MSG(sizeof(Int1) == 1, "Int1 is not of the correct size");
BOOST_STATIC_ASSERT_MSG(sizeof(Int2) == 2, "Int2 is not of the correct size");
BOOST_STATIC_ASSERT_MSG(sizeof(Int4) == 4, "Int4 is not of the correct size");
BOOST_STATIC_ASSERT_MSG(sizeof(Int8) == 8, "Int8 is not of the correct size");
BOOST_STATIC_ASSERT_MSG(sizeof(Num1) == 1, "Num1 is not of the correct size");
BOOST_STATIC_ASSERT_MSG(sizeof(Num2) == 2, "Num2 is not of the correct size");
BOOST_STATIC_ASSERT_MSG(sizeof(Num4) == 4, "Num4 is not of the correct size");
BOOST_STATIC_ASSERT_MSG(sizeof(Num8) == 8, "Num8 is not of the correct size");
