CC = g++
CFLAGS = -c -Wall
OBJECTS= main.o entity.o player.o enemy.o gameEnvironment.o game.o coordinate.o weapon.o rangedWeapon.o item.o
LIBRARY = -lncursesw

main: $(OBJECTS)
		$(CC) -o main $(OBJECTS) $(LIBRARY)

main.o: main.cpp src/entity/entity.hpp src/entity/player.hpp src/entity/enemy.hpp src/gameEnvironment/gameEnvironment.hpp src/gameEnvironment/coordinate.hpp src/weapon/weapon.hpp src/weapon/rangedWeapon.hpp src/item/item.hpp 
		$(CC) $(CFLAGS) main.cpp

entity.o: src/entity/entity.cpp src/entity/entity.hpp
		$(CC) $(CFLAGS) src/entity/entity.cpp
		
player.o: src/entity/player.hpp src/entity/player.cpp
		$(CC) $(CFLAGS) src/entity/player.cpp

enemy.o: src/entity/enemy.hpp src/entity/enemy.cpp
		$(CC) $(CFLAGS) src/entity/enemy.cpp

gameEnvironment.o: src/gameEnvironment/gameEnvironment.hpp src/gameEnvironment/gameEnvironment.cpp
		$(CC) $(CFLAGS) src/gameEnvironment/gameEnvironment.cpp

game.o: src/game/game.hpp src/game/game.cpp
		$(CC) $(CFLAGS) src/game/game.cpp

coordinate.o: src/gameEnvironment/coordinate.hpp src/gameEnvironment/coordinate.cpp
		$(CC) $(CFLAGS) src/gameEnvironment/coordinate.cpp

weapon.o: src/weapon/weapon.hpp src/weapon/weapon.cpp
		$(CC) $(CFLAGS) src/weapon/weapon.cpp

rangedWeapon.o: src/weapon/rangedWeapon.hpp src/weapon/rangedWeapon.cpp
		$(CC) $(CFLAGS) src/weapon/rangedWeapon.cpp

item.o: src/item/item.hpp src/item/item.cpp
		$(CC) $(CFLAGS) src/item/item.cpp



launch: 
		sort -k2 -n -r -o scoreboard.txt scoreboard.txt
		./main
	
clean:
		rm *.o main

scoreboard:
		sort -k2 -n -r -o scoreboard.txt scoreboard.txt

	


