# -----------------------------------------------------------------------------
# CannonBall CMake setup
#
# For ports, please try not to edit this file directly.
# Everything should go into a Win64.cmake equivalent.
# -----------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.3.2) # Might compile lower, but untested
project (CannonBall)

# -----------------------------------------------------------------------------
# Directory Setup
# -----------------------------------------------------------------------------

# CMake default file (override with -DTARGET=file)
set(DCMAKE Win64-GL.cmake)

# Source location
set(SrcDir ..)

# -----------------------------------------------------------------------------
# Platform Specific Setup
# -----------------------------------------------------------------------------

# Include relevant CMAKE file (default, mingw, pandora etc.)
if(TARGET)
    if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${TARGET}")
        message("CMake files for ${TARGET} found")
        include(${TARGET})
    else()
        message("CMake files for ${TARGET} not found, using ${DCMAKE}")
        include(${DCMAKE})
    endif()
else()
    message("TARGET not passed, using ${DCMAKE}")
    include(${DCMAKE})
endif(TARGET)

# -----------------------------------------------------------------------------
# Project Source Files
# -----------------------------------------------------------------------------

set(Src
    "${SrcDir}/Globals.hpp"
    "${SrcDir}/LoadROM.hpp"
    "${SrcDir}/ROMs.hpp"
    "${SrcDir}/LoadTrack.hpp"
    "${SrcDir}/Types.hpp"
    "${SrcDir}/Main.hpp"
    "${SrcDir}/Video.hpp"
    "${SrcDir}/Utils.hpp"
    "${SrcDir}/DirEnt.h"

    "${SrcDir}/Main.cpp"
    "${SrcDir}/LoadROM.cpp"
    "${SrcDir}/LoadTrack.cpp"
    "${SrcDir}/ROMs.cpp"
    "${SrcDir}/Video.cpp"
    "${SrcDir}/Utils.cpp"
    )

set(ArenaSrc
    "${SrcDir}/Arena/PitStop.hpp"
    "${SrcDir}/Arena/Config.hpp"
    "${SrcDir}/Arena/Menu.hpp"
    "${SrcDir}/Arena/MenuLabels.hpp"
    "${SrcDir}/Arena/Laps.hpp"

    "${SrcDir}/Arena/PitStop.cpp"
    "${SrcDir}/Arena/Config.cpp"
    "${SrcDir}/Arena/Menu.cpp"
    "${SrcDir}/Arena/Laps.cpp"
    )

set(VideoSrc
    "${SrcDir}/Video/Road.hpp"
    "${SrcDir}/Video/Sprites.hpp"
    "${SrcDir}/Video/Tiles.hpp"

    "${SrcDir}/Video/Road.cpp"
    "${SrcDir}/Video/Sprites.cpp"
    "${SrcDir}/Video/Tiles.cpp"
    )

set(AudioSrc
    "${SrcDir}/Audio/SegaPCM.hpp"
    "${SrcDir}/Audio/SoundChip.hpp"
    "${SrcDir}/Audio/YM2151.hpp"

    "${SrcDir}/Audio/SegaPCM.cpp"
    "${SrcDir}/Audio/SoundChip.cpp"
    "${SrcDir}/Audio/YM2151.cpp"
    )

set(PlaySrc
	"${SrcDir}/Play/Audio.hpp"
	"${SrcDir}/Play/Timer.hpp"
	"${SrcDir}/Play/Input.hpp"
	"${SrcDir}/Play/RenderBase.hpp"

    "${SrcDir}/Play/Audio.cpp"
	"${SrcDir}/Play/Timer.cpp"
	"${SrcDir}/Play/Input.cpp"
	"${SrcDir}/Play/RenderBase.cpp"
    )

if(OPENGL)
	set(RenderSrc
	    "${SrcDir}/Play/RenderGL.hpp"
	    "${SrcDir}/Play/RenderGL.cpp"
	)
elseif(OPENGLES)
	set(RenderSrc
	    "${SrcDir}/Play/RenderGLES.hpp"
	    "${SrcDir}/Play/RenderGLES.cpp"
	)
else()
	set(RenderSrc
	    "${SrcDir}/Play/RenderSurface.hpp"
	    "${SrcDir}/Play/RenderSurface.cpp"
	)
endif()

set(JoltSrc
    "${SrcDir}/Jolt/Jolt.hpp"
    "${SrcDir}/Jolt/Jolt.cpp"
)

set(GameSrc
    "${SrcDir}/Game/Addresses.hpp"
    "${SrcDir}/Game/Animation.hpp"
    "${SrcDir}/Game/SpriteMove.hpp"
    "${SrcDir}/Game/AttractAI.hpp"
    "${SrcDir}/Game/Bonus.hpp"
    "${SrcDir}/Game/Crash.hpp"
    "${SrcDir}/Game/SpriteEntry.hpp"
    "${SrcDir}/Game/Ferrari.hpp"
    "${SrcDir}/Game/HiScore.hpp"
    "${SrcDir}/Game/Display.hpp"
    "${SrcDir}/Game/InitGame.hpp"
    "${SrcDir}/Game/Inputs.hpp"
    "${SrcDir}/Game/LevelObjs.hpp"
    "${SrcDir}/Game/Logo.hpp"
    "${SrcDir}/Game/Map.hpp"
    "${SrcDir}/Game/Music.hpp"
    "${SrcDir}/Game/Outputs.hpp"
    "${SrcDir}/Game/Palette.hpp"
    "${SrcDir}/Game/Road.hpp"
    "${SrcDir}/Game/Smoke.hpp"
    "${SrcDir}/Game/Sprite.hpp"
    "${SrcDir}/Game/Sprites.hpp"
    "${SrcDir}/Game/Stats.hpp"
    "${SrcDir}/Game/Tiles.hpp"
    "${SrcDir}/Game/Traffic.hpp"
    "${SrcDir}/Game/Tools.hpp"
    "${SrcDir}/Game/OutRun.hpp"

    "${SrcDir}/Game/Animation.cpp"
    "${SrcDir}/Game/AttractAI.cpp"
    "${SrcDir}/Game/Bonus.cpp"
    "${SrcDir}/Game/Crash.cpp"
    "${SrcDir}/Game/Ferrari.cpp"
    "${SrcDir}/Game/HiScore.cpp"
    "${SrcDir}/Game/Display.cpp"
    "${SrcDir}/Game/InitGame.cpp"
    "${SrcDir}/Game/Inputs.cpp"
    "${SrcDir}/Game/LevelObjs.cpp"
    "${SrcDir}/Game/Logo.cpp"
    "${SrcDir}/Game/Map.cpp"
    "${SrcDir}/Game/Music.cpp"
    "${SrcDir}/Game/Outputs.cpp"
    "${SrcDir}/Game/Palette.cpp"
    "${SrcDir}/Game/Road.cpp"
    "${SrcDir}/Game/Smoke.cpp"
    "${SrcDir}/Game/Sprite.cpp"
    "${SrcDir}/Game/Sprites.cpp"
    "${SrcDir}/Game/Stats.cpp"
    "${SrcDir}/Game/Tiles.cpp"
    "${SrcDir}/Game/Traffic.cpp"
    "${SrcDir}/Game/Tools.cpp"
    "${SrcDir}/Game/OutRun.cpp"
    )

set(GameDataSrc
    "${SrcDir}/Game/Data/ZoomTable.hpp"
    "${SrcDir}/Game/Data/SpritePals.hpp"
    )

set(GameSoundSrc
    "${SrcDir}/Game/Sound/Commands.hpp"
    "${SrcDir}/Game/Sound/Sound.hpp"
    "${SrcDir}/Game/Sound/SoundInt.hpp"
    "${SrcDir}/Game/Sound/SoundAddr.hpp"

    "${SrcDir}/Game/Sound/Sound.cpp"
    "${SrcDir}/Game/Sound/SoundInt.cpp"
    )

set(Srcs
    ${Src}
    ${ArenaSrc}
    ${VideoSrc}
    ${AudioSrc}
    ${PlaySrc}
    ${RenderSrc}
    ${JoltSrc}
    ${GameSrc}
    ${GameDataSrc}
    ${GameSoundSrc}
)

# Group files into relevant filters for Visual Studio build
SOURCE_GROUP(.. FILES ${Src})
SOURCE_GROUP(..\\Arena FILES ${ArenaSrc})
SOURCE_GROUP(..\\Video FILES ${VideoSrc})
SOURCE_GROUP(..\\Audio FILES ${AudioSrc})
SOURCE_GROUP(..\\Play FILES ${PlaySrc})
SOURCE_GROUP(..\\Play FILES ${RenderSrc})
SOURCE_GROUP(..\\Jolt FILES ${JoltSrc})
SOURCE_GROUP(..\\Game FILES ${GameSrc})
SOURCE_GROUP(..\\Game\\Data FILES ${GameDataSrc})
SOURCE_GROUP(..\\Game\\Sound FILES ${GameSoundSrc})

# Add Icon For Windows Builds
if(WIN32)
  set(Srcs ${Srcs} ../Res/CannonBall.rc)
endif(WIN32)

add_executable(CannonBall ${Srcs})

# -----------------------------------------------------------------------------
# Compiler Definitions
# -----------------------------------------------------------------------------

if(OPENGL)
    add_definitions(-DWITH_OPENGL)
endif()

if(OPENGLES)
    add_definitions(-DWITH_OPENGLES)
endif()

# -----------------------------------------------------------------------------
# Library Setup
# -----------------------------------------------------------------------------

set(BOOST_INCLUDEDIR ${BoostDir})
find_package(Boost REQUIRED)

set(SDL2_DIR ${Sdl2Dir})
find_package(SDL2 REQUIRED)
message("SDL2 Include  : ${SDL2_INCLUDE_DIRS}")
message("SDL2 Libraries: ${SDL2_LIBRARIES}")

# Include
include_directories(
    ${SrcDir}
    ${BOOST_INCLUDEDIR}
    ${SDL2_INCLUDE_DIRS}
)

link_directories(
    ${PlatformLinkDirs}
)

target_link_libraries(CannonBall
    ${SDL2_LIBRARIES}
    ${PlatformLinkLibs}
)

# -----------------------------------------------------------------------------
# Copy useful files to build destination
# -----------------------------------------------------------------------------

configure_file(../Res/Config.xml ./Config.xml
    COPYONLY
)

configure_file(../Res/TileMap.bin ./Res/TileMap.bin
    COPYONLY
)
configure_file(../Res/TilePatch.bin ./Res/TilePatch.bin
    COPYONLY
)
configure_file(../Res/ConsoleDB.txt ./Res/ConsoleDB.txt
    COPYONLY
)
