CC=/usr/bin/g++
CFLAGS=-g -std=c++17
LDFLAGS=-lboost_system -lboost_serialization -lpthread -lconfig++ -lconfig
EXEC=r-type_server
SRC=$(wildcard server/sources/*.cpp Core/*.cpp Sockets/sources/*.cpp ECS/Systems/*.cpp ECS/Systems/Subsystems/*.cpp ECS/Entity/*.cpp gameLoop/*.cpp gameLoop/RTypeGameLoop/*.cpp EntityTypes/*.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)

mrproper: clean
	rm -rf $(EXEC)
