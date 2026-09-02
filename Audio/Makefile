all: All.a

SegaPCM.o: SegaPCM.cpp
	@g++ -c $^ -I${SrcDir}
SoundChip.o: SoundChip.cpp
	@g++ -c $^ -I${SrcDir}
YM2151.o: YM2151.cpp
	@g++ -c $^ -I${SrcDir}
Objs=SegaPCM.o SoundChip.o YM2151.o

All.a: ${Objs}
	@${AR} rcs $@ $^

clean:
	@${RM} ${Objs}
	@${RM} All.a

## Local dependencies.
SegaPCM.cpp: SegaPCM.hpp
SoundChip.cpp: SoundChip.hpp
YM2151.cpp: YM2151.hpp
SegaPCM.hpp YM2151.hpp: SoundChip.hpp

## Non-local dependencies.
SegaPCM.hpp YM2151.hpp: ../LoadROM.hpp
SegaPCM.hpp SoundChip.cpp YM2151.hpp: ../Types.hpp
