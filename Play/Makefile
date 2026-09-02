all: All.a

Audio.o: Audio.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Input.o: Input.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
RenderBase.o: RenderBase.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Render.o: Render.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir} ${RenderOpt}
Timer.o: Timer.cpp
	@g++ -c $^ -I${SrcDir} -I${SdlDir}
Objs=Audio.o Input.o RenderBase.o Render.o Timer.o

All.a: ${Objs}
	@${AR} rcs $@ $^

clean:
	@${RM} ${Objs}
	@${RM} All.a

## Local dependencies.
Audio.cpp: Audio.hpp
Input.cpp: Input.hpp
Render.cpp: Render.hpp RenderBase.hpp
RenderBase.cpp: RenderBase.hpp
Timer.cpp: Timer.hpp

## Non-local dependencies.
Audio.cpp: ../Game/Sound/SoundInt.hpp
Audio.cpp Render.cpp: ../Arena/Config.hpp
Audio.hpp RenderBase.hpp: ../Globals.hpp
Input.hpp RenderBase.hpp: ../Types.hpp
