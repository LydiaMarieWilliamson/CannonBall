SrcDir=${CURDIR}
export SrcDir
SdlDir=/usr/include/SDL2
export SdlDir
RM=rm -f
export RM
RenderOpt=-DWITH_OPENGL
## RenderOpt=-DWITH_OPENGLES
## RenderOpt=
export RenderOpt

## pkg-config --cflags sdl2
## pkg-config --cflags opengl
CFLAGS=-I${SdlDir} -D_GNU_SOURCE=1 -D_REENTRANT
## pkg-config --libs sdl2
## pkg-config --libs opengl
LIBS=-lSDL2 -lOpenGL

all: CannonBall Config.xml

Main.o: Main.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
LoadROM.o: LoadROM.cpp
	@g++ -c $^ -I${SrcDir}
ROMs.o: ROMs.cpp
	@g++ -c $^
LoadTrack.o: LoadTrack.cpp
	@g++ -c $^ -I${SrcDir}
Utils.o: Utils.cpp
	@g++ -c $^
Video.o: Video.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir} ${RenderOpt}
Objs=Main.o LoadROM.o ROMs.o LoadTrack.o Utils.o Video.o

Game/Sound/All.a:
	@${MAKE} -C Game Sound/All.a
SubSubs=Game/Sound/All.a

Jolt/All.a:
	@${MAKE} -C Jolt
Game/All.a:
	@${MAKE} -C Game
Arena/All.a:
	@${MAKE} -C Arena
Audio/All.a:
	@${MAKE} -C Audio
Video/All.a:
	@${MAKE} -C Video
Play/All.a:
	@${MAKE} -C Play
Subs=Jolt/All.a Game/All.a Arena/All.a Audio/All.a Video/All.a Play/All.a

CannonBall: ${Objs} ${SubSubs} ${Subs}
	@g++ $^ ${CFLAGS} ${RenderOpt} ${LIBS} -o $@
Config.xml:
	@cp Res/Config.xml .

TopFiles=TopPlay.xml TopPlayJap.xml TopLaps.xml TopLapsJap.xml TopRuns.xml TopRunsJap.xml

clean:
	@${RM} ${Objs}
	@${MAKE} -C Jolt clean
	@${MAKE} -C Game clean
	@${MAKE} -C Arena clean
	@${MAKE} -C Audio clean
	@${MAKE} -C Video clean
	@${MAKE} -C Play clean
clobber: clean
	@${RM} CannonBall
	@${RM} Config.xml
	@${RM} ${TopFiles}

## Local dependencies.
LoadROM.cpp: DirEnt.h LoadROM.hpp Types.hpp
LoadTrack.cpp: LoadTrack.hpp ROMs.hpp
Main.cpp: LoadROM.hpp LoadTrack.hpp Main.hpp Types.hpp Video.hpp
ROMs.cpp: ROMs.hpp Types.hpp
Utils.cpp: Utils.hpp
Video.cpp: Globals.hpp Video.hpp
LoadTrack.hpp Main.hpp Video.hpp: Globals.hpp
Globals.hpp Utils.hpp Video.hpp: Types.hpp
ROMs.hpp: LoadROM.hpp
Video.hpp: ROMs.hpp

## Non-local dependencies.
LoadROM.cpp: Arena/Config.hpp
LoadTrack.cpp: Game/Addresses.hpp Game/OutRun.hpp
Main.cpp Video.cpp: Arena/Config.hpp
Main.cpp: Arena/Menu.hpp
Main.cpp: Game/Inputs.hpp Game/Music.hpp Game/OutRun.hpp Game/Outputs.hpp
Video.cpp: Game/Road.hpp
Main.cpp: Jolt/Jolt.hpp
Main.cpp: Play/Input.hpp Play/Timer.hpp Play/Audio.hpp
Video.cpp: Play/Render.hpp
Video.hpp: Video/Road.hpp Video/Sprites.hpp Video/Tiles.hpp
