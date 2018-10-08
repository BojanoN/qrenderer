PROJECT = qrender
MAIN = $(wildcard *.cpp)
MATLIBIMP = $(wildcard matlib/*.cpp)
MATLIBHEAD = $(wildcard matlib/*.hpp)
TYPES = $(wildcard types/*.hpp)

MATLIBOBJ = ${MATLIBIMP:.cpp=.o}
MAINOBJ = main.o


CC = g++
CFLAGS = -g -O3
GLFLAGS = -lGL -lGLU 
SDLFLAGS = -lSDL2 -lpthread -lSDL2_ttf
ZIPFLAGS = -lzip
SOILFLAGS = -lSOIL

all:$(MATLIBOBJ) $(GLTEXTOBJ)
	$(CC) $(CFLAGS) $(GLFLAGS) $(MATLIBOBJ) $(MAIN) $(SDLFLAGS) $(ZIPFLAGS) $(SOILFLAGS) -o $(PROJECT)

$(MATLIBOBJ):$(MATLIBHEAD) $(TYPES)


clean:
	-rm -f *.o *.core $(PROJECT)
