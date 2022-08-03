CC = g++
CFLAGS = -c -Wall
OBJECTS= main.o entity.o player.o enemy.o gameEnvironment.o coordinate.o weapon.o rangedWeapon.o item.o power.o artifact.o 
LIBRARY = -lncurses

main: $(OBJECTS)
		$(CC) -o main $(OBJECTS) $(LIBRARY)

main.o: main.cpp entity/entity.hpp entity/player.hpp entity/enemy.hpp gameEnvironment/gameEnvironment.hpp gameEnvironment/coordinate.hpp weapon/weapon.hpp weapon/rangedWeapon.hpp item/item.hpp item/power.hpp item/artifact.hpp
		$(CC) $(CFLAGS) main.cpp

entity.o: entity/entity.hpp entity/entity.cpp
		$(CC) $(CFLAGS) entity/entity.cpp
		
player.o: entity/player.hpp entity/player.cpp
		$(CC) $(CFLAGS) entity/player.cpp

enemy.o: entity/enemy.hpp entity/enemy.cpp
		$(CC) $(CFLAGS) entity/enemy.cpp

gameEnvironment.o: gameEnvironment/gameEnvironment.hpp gameEnvironment/gameEnvironment.cpp
		$(CC) $(CFLAGS) gameEnvironment/gameEnvironment.cpp

coordinate.o: gameEnvironment/coordinate.hpp gameEnvironment/coordinate.cpp
		$(CC) $(CFLAGS) gameEnvironment/coordinate.cpp

weapon.o: weapon/weapon.hpp weapon/weapon.cpp
		$(CC) $(CFLAGS) weapon/weapon.cpp

weapon.o: weapon/rangedWeapon.hpp weapon/rangedWeapon.cpp
		$(CC) $(CFLAGS) weapon/rangedWeapon.cpp

item.o: item/item.hpp item/item.cpp
		$(CC) $(CFLAGS) item/item.cpp

power.o: item/power.hpp item/power.cpp
		$(CC) $(CFLAGS) item/power.cpp

artifact.o: item/artifact.hpp item/artifact.cpp
		$(CC) $(CFLAGS) item/artifact.cpp

launch: 
		./main
	
clean:
		rm *.o main
	


