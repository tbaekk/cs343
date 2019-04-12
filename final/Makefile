CXX = u++					# compiler
CXXFLAGS = -g -multi -O2 -std=c++14 -Wall -Wextra -MMD # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}# makefile name

OBJECTS1 = internalsyncLOCK.o		# optional build of given program
EXEC1 = internalsyncLOCK			# given executable name

OBJECTS2 = barrier.o
EXEC2 = barrier

OBJECTS3 = barrierADD.o
EXEC3 = barrierADD

OBJECTS4 = cntsemSYNC.o
EXEC4 = cntsemSYNC

OBJECTS5 = cntsemMUTEX.o
EXEC5 = cntsemMUTEX

OBJECTS6 = boundedbufferEXT.o
EXEC6 = boundedbufferEXT

OBJECTS7 = boundedbufferINT.o
EXEC7 = boundedbufferINT

OBJECTS = ${OBJECTS1} ${OBJECTS2} ${OBJECTS3} ${OBJECTS4} ${OBJECTS5} ${OBJECTS6} ${OBJECTS7}
DEPENDS = ${OBJECTS:.o=.d}
EXECS = ${EXEC1} ${EXEC2} ${EXEC3} ${EXEC4} ${EXEC5} ${EXEC6} ${EXEC7}

#############################################################

.PHONY : all clean

all : ${EXECS}				# build all executables

${EXEC1} : ${OBJECTS1}
	u++ ${CXXFLAGS} $^ -o $@

${EXEC2} : ${OBJECTS2}
	u++ ${CXXFLAGS} $^ -o $@

${EXEC3} : ${OBJECTS3}
	u++ ${CXXFLAGS} $^ -o $@

${EXEC4} : ${OBJECTS4}
	u++ ${CXXFLAGS} $^ -o $@

${EXEC5} : ${OBJECTS5}
	u++ ${CXXFLAGS} $^ -o $@

${EXEC6} : ${OBJECTS6}
	u++ ${CXXFLAGS} $^ -o $@

${EXEC7} : ${OBJECTS7}
	u++ ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}		# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}			# include *.d files containing program dependences

clean :					# remove files that can be regenerated
	rm -f *.d *.o ${EXECS}