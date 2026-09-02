all: All.a

Sound.o: Sound.cpp
	@g++ -c $^ -I${SrcDir}
SoundInt.o: SoundInt.cpp
	@g++ -c $^ -I${SrcDir}
Objs=Sound.o SoundInt.o

All.a: ${Objs}
	@${AR} rcs $@ $^

clean:
	@${RM} ${Objs}
	@${RM} All.a

## Local dependencies.
Sound.cpp: Sound.hpp
SoundInt.cpp: SoundInt.hpp Sound.hpp
SoundInt.hpp: Commands.hpp
Sound.hpp SoundInt.hpp: Commands.hpp
Sound.hpp: SoundAddr.hpp

## Non-local dependencies.
Sound.hpp: ../../Audio/YM2151.hpp ../../Globals.hpp ../../ROMs.hpp ../../Types.hpp
SoundInt.hpp: ../../Audio/SegaPCM.hpp ../../Audio/YM2151.hpp
