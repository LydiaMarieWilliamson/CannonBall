all: All.a

Road.o: Road.cpp
	@g++ -c $^ -I${SrcDir}
Sprites.o: Sprites.cpp
	@g++ -c $^ -I${SrcDir}
Tiles.o: Tiles.cpp
	@g++ -c $^ -I${SrcDir}
Objs=Road.o Sprites.o Tiles.o

All.a: ${Objs}
	@${AR} rcs $@ $^

clean:
	@${RM} ${Objs}
	@${RM} All.a

## Local dependencies.
Road.cpp: Road.hpp
Sprites.cpp: Sprites.hpp
Tiles.cpp: Tiles.hpp

## Non-local dependencies.
Road.cpp Sprites.cpp Tiles.cpp: ../Globals.hpp ../Arena/Config.hpp
Road.hpp Sprites.hpp Tiles.hpp: ../Types.hpp
Sprites.cpp: ../Video.hpp
Tiles.cpp: ../LoadROM.hpp
