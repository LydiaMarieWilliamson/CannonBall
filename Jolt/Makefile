all: All.a

Jolt.o: Jolt.cpp
	@g++ -c $^ -I${SrcDir}
Objs=Jolt.o

All.a: ${Objs}
	@${AR} rcs $@ $^

clean:
	@${RM} ${Objs}
	@${RM} All.a

## Local dependencies.
Jolt.cpp: Jolt.hpp
