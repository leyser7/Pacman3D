SRC = ./src
CFLAGS=-I./include
LDFLAGS=-lGLU -lGL -lglut
OBJS=obj/myfuncs.o obj/mytypes.o obj/text3d.o

all: $(OBJS)
	$(CXX) $(CFLAGS) -o pacman $(SRC)/main.cpp $(OBJS) $(LDFLAGS) 

obj/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean: 
	rm -rf obj/*