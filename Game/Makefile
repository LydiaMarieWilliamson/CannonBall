all: All.a Sound/All.a

Animation.o: Animation.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
AttractAI.o: AttractAI.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Bonus.o: Bonus.cpp
	@g++ -c $^ -I${SrcDir}
Crash.o: Crash.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Ferrari.o: Ferrari.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Tops.o: Tops.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Display.o: Display.cpp
	@g++ -c $^ -I${SrcDir}
InitGame.o: InitGame.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Inputs.o: Inputs.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
LevelObjs.o: LevelObjs.cpp
	@g++ -c $^ -I${SrcDir}
Logo.o: Logo.cpp
	@g++ -c $^ -I${SrcDir}
Map.o: Map.cpp
	@g++ -c $^ -I${SrcDir}
Music.o: Music.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Outputs.o: Outputs.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Palette.o: Palette.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Road.o: Road.cpp
	@g++ -c $^ -I${SrcDir}
Smoke.o: Smoke.cpp
	@g++ -c $^ -I${SrcDir}
Sprite.o: Sprite.cpp
	@g++ -c $^ -I${SrcDir}
Sprites.o: Sprites.cpp
	@g++ -c $^ -I${SrcDir}
Stats.o: Stats.cpp
	@g++ -c $^ -I${SrcDir}
Tiles.o: Tiles.cpp
	@g++ -c $^ -I${SrcDir}
Traffic.o: Traffic.cpp
	@g++ -c $^ -I${SrcDir}
Tools.o: Tools.cpp
	@g++ -c $^ -I${SrcDir}
OutRun.o: OutRun.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Objs= \
	Animation.o AttractAI.o Bonus.o Crash.o Ferrari.o Tops.o Display.o InitGame.o \
	Inputs.o LevelObjs.o Logo.o Map.o Music.o Outputs.o Palette.o Road.o \
	Smoke.o Sprite.o Sprites.o Stats.o Tiles.o Traffic.o Tools.o OutRun.o

Sound/All.a:
	@${MAKE} -C Sound

All.a: ${Objs}
	@${AR} rcs $@ $^

clean:
	@${RM} ${Objs}
	@${RM} All.a
	@${MAKE} -C Sound clean

## Local dependencies.
Animation.cpp: Animation.hpp Bonus.hpp Ferrari.hpp Inputs.hpp
AttractAI.cpp: AttractAI.hpp Ferrari.hpp Inputs.hpp Stats.hpp Traffic.hpp
Bonus.cpp: Bonus.hpp Display.hpp Tools.hpp Stats.hpp
Crash.cpp: Crash.hpp Ferrari.hpp Tools.hpp Inputs.hpp LevelObjs.hpp
Display.cpp: Display.hpp Ferrari.hpp Tools.hpp Outputs.hpp Stats.hpp
Ferrari.cpp: Animation.hpp AttractAI.hpp Bonus.hpp Crash.hpp Display.hpp Ferrari.hpp Tools.hpp Inputs.hpp LevelObjs.hpp Outputs.hpp Stats.hpp
Tools.cpp: Tools.hpp Stats.hpp
Tops.cpp: Display.hpp Tools.hpp Tops.hpp Inputs.hpp Stats.hpp
InitGame.cpp: Animation.hpp Bonus.hpp Crash.hpp Display.hpp Ferrari.hpp Tools.hpp InitGame.hpp Inputs.hpp LevelObjs.hpp Music.hpp Outputs.hpp Palette.hpp Smoke.hpp Stats.hpp Tiles.hpp Traffic.hpp
Inputs.cpp: Crash.hpp Inputs.hpp Stats.hpp
LevelObjs.cpp: Tools.hpp LevelObjs.hpp Stats.hpp
Logo.cpp: Tools.hpp Logo.hpp Sprites.hpp
Map.cpp: Ferrari.hpp Map.hpp Stats.hpp Tiles.hpp Traffic.hpp
Music.cpp: Display.hpp Ferrari.hpp Inputs.hpp Logo.hpp Music.hpp Stats.hpp Tiles.hpp Traffic.hpp
OutRun.cpp: Animation.hpp AttractAI.hpp Bonus.hpp Crash.hpp Display.hpp Ferrari.hpp Tools.hpp Tops.hpp Inputs.hpp LevelObjs.hpp Logo.hpp Map.hpp Music.hpp OutRun.hpp Outputs.hpp Palette.hpp Smoke.hpp Stats.hpp Tiles.hpp Traffic.hpp
Outputs.cpp: Crash.hpp Display.hpp Ferrari.hpp Inputs.hpp OutRun.hpp Outputs.hpp
Palette.cpp: Display.hpp Inputs.hpp Palette.hpp
Road.cpp: Addresses.hpp Tools.hpp InitGame.hpp Road.hpp Stats.hpp
Smoke.cpp: Crash.hpp Ferrari.hpp LevelObjs.hpp Smoke.hpp
Sprite.cpp: Sprite.hpp
Sprites.cpp: Animation.hpp Crash.hpp Data/ZoomTable.hpp Ferrari.hpp LevelObjs.hpp Sprites.hpp Traffic.hpp
Stats.cpp: Display.hpp Tools.hpp Music.hpp Stats.hpp Traffic.hpp
Tiles.cpp: Palette.hpp Tiles.hpp
Traffic.cpp: Bonus.hpp Crash.hpp Display.hpp Ferrari.hpp Tools.hpp LevelObjs.hpp Stats.hpp Traffic.hpp
AttractAI.hpp Bonus.hpp Crash.hpp Display.hpp Ferrari.hpp InitGame.hpp Inputs.hpp LevelObjs.hpp Map.hpp Music.hpp Palette.hpp Smoke.hpp Sprites.hpp Stats.hpp Tiles.hpp Traffic.hpp: OutRun.hpp
Animation.hpp: SpriteMove.hpp
OutRun.hpp: Addresses.hpp InitGame.hpp Road.hpp Sprites.hpp Sound/SoundInt.cpp
SpriteMove.hpp: SpriteEntry.hpp
Sprites.hpp: Sprite.hpp SpriteEntry.hpp Data/SpritePals.hpp

## Non-local dependencies.
Data/SpritePals.hpp Data/ZoomTable.hpp: ../Types.hpp
Tools.hpp Tops.hpp Logo.cpp OutRun.hpp Outputs.hpp Road.cpp Sprite.hpp SpriteEntry.hpp: ../Types.hpp
InitGame.cpp LevelObjs.cpp OutRun.cpp Palette.cpp Road.cpp Sprites.cpp Tiles.cpp: ../LoadTrack.hpp
Display.cpp OutRun.cpp Outputs.cpp: ../Utils.hpp
Tops.cpp Music.cpp OutRun.cpp: ../Main.hpp
Animation.cpp OutRun.hpp: ../Arena/Config.hpp
OutRun.hpp Road.cpp: ../Globals.hpp ../ROMs.hpp
Inputs.hpp: ../Play/Input.hpp
OutRun.hpp: Sound/SoundInt.hpp ../Video.hpp
Outputs.cpp: ../Jolt/Jolt.hpp
