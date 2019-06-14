all:
	g++ World.cpp Organism.cpp Animal.cpp Plant.cpp Grass.cpp Sowthistle.cpp Guarana.cpp Deadly_nightshade.cpp Heracleum_sosnowskyi.cpp Cybersheep.cpp Sheep.cpp Wolf.cpp Fox.cpp Turtle.cpp Antelope.cpp Human.cpp main.cpp -o main \
	-std=c++17 \
	-Werror=narrowing