all: bin/hamming.o main.cpp
	@g++ -std=c++17 main.cpp bin/hamming.o -o bin/main

bin/hamming.o : src/Hamming/src/hamming.cpp src/Hamming/include/hamming.h
	@g++ -std=c++17 -c src/Hamming/src/hamming.cpp -o bin/hamming.o 
