CXX=g++
CXXFLAGS=-std=c++17 -ggdb -Wall
LIBS=-lfmt

SRC=$(wildcard src/*.cpp)
OBJS=$(addprefix obj/, $(SRC:.cpp=.o))

.PHONY: dirs

all: dirs target

target: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS)

obj/src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -rf obj/

dirs:
	mkdir -p obj/src
