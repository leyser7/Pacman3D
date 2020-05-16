CFLAGS= -I./include
LDFLAGS=-lSDL -lm -lSDL_net -lGL -lGLU -lSDL_mixer -lglut -lGLU -lGL
OBJS=

all: pacman

pacman: $(OBJS)
        $(CXX) $(CFLAGS) -o pacman src/Maquette/Main.cpp $(OBJS) $(LDFLAGS)

%.o: %.c
        $(CXX) $(CFLAGS) -c $< $(LDFLAGS) $(OBJS)

clean:
        rm -f pacman $(OBJS) 
