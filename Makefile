CXX = g++
CXXFLAGS = -std=c++14 -g -O0 -Wall -MMD -Werror=vla 
OBJECTS = main.o grid.o cell.o subject.o textdisplay.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = a4q3

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

%.o : %.cc
	${CXX} ${CXXFLAGS} -c $< 

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
