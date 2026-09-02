all: All.a

PitStop.o: PitStop.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Config.o: Config.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Menu.o: Menu.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Laps.o: Laps.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Objs=PitStop.o Config.o Menu.o Laps.o

All.a: ${Objs}
	@${AR} rcs $@ $^

clean:
	@${RM} ${Objs}
	@${RM} All.a

## Local dependencies.
Config.cpp: Config.hpp
Laps.cpp: Laps.hpp
Menu.cpp: Menu.hpp MenuLabels.hpp Laps.hpp PitStop.hpp
PitStop.cpp: PitStop.hpp

## Non-local dependencies.
Config.hpp Laps.hpp Menu.hpp PitStop.hpp: ../Types.hpp
Config.cpp Menu.cpp PitStop.cpp: ../Utils.hpp
Config.cpp Menu.cpp: ../Main.hpp
Config.cpp: ../Globals.hpp
PitStop.cpp: ../Video.hpp
Laps.cpp PitStop.cpp: ../Play/Input.hpp
Laps.cpp Menu.cpp PitStop.cpp: ../Game/Display.hpp ../Game/Tiles.hpp
Config.cpp Laps.cpp: ../Game/Tools.hpp
Laps.cpp Menu.cpp: ../Game/Inputs.hpp
Config.cpp Config.cpp: ../Game/Sound/SoundInt.hpp
Laps.cpp Laps.cpp: ../Game/Stats.hpp
Menu.cpp Menu.cpp Menu.cpp Menu.cpp: ../Game/Sprites.hpp
PitStop.cpp PitStop.cpp: ../Game/Outputs.hpp
