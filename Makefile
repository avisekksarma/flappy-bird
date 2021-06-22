CC=g++
EXEC=game

GAME_FOLDER=./Game
PLAYER_FOLDER=./Player
ENTITY_FOLDER=./Entity

FLAGS="-std=c++11"
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

$(EXEC): main.o game.o player.o background.o obstacle.o
	$(CC) main.o game.o player.o background.o obstacle.o $(FLAGS) $(SFML_FLAGS) -g -o $(EXEC) 

main.o: main.cpp
	$(CC) $(FLAGS) -c -g main.cpp

game.o: $(GAME_FOLDER)/game.cpp
	$(CC) $(FLAGS) -c -g $(GAME_FOLDER)/game.cpp

player.o: $(PLAYER_FOLDER)/player.cpp
	$(CC) $(FLAGS) -c -g $(PLAYER_FOLDER)/player.cpp

background.o: $(ENTITY_FOLDER)/background.cpp
	$(CC) $(FLAGS) -c -g $(ENTITY_FOLDER)/background.cpp

obstacle.o: $(ENTITY_FOLDER)/obstacle.cpp
	$(CC) $(FLAGS) -c -g $(ENTITY_FOLDER)/obstacle.cpp

clean:
	rm *.o $(EXEC)