all: bin/hamming.o main.cpp coder.cpp decoder.cpp
	@g++ -std=c++17 main.cpp bin/hamming.o -o bin/main
	@g++ -std=c++17 coder.cpp bin/hamming.o -o bin/coder
	@g++ -std=c++17 decoder.cpp bin/hamming.o -o bin/decoder
	@g++ -std=c++17 demon.cpp bin/hamming.o -o bin/demon

bin/hamming.o : src/Hamming/src/hamming.cpp src/Hamming/include/hamming.h
	@g++ -std=c++17 -c src/Hamming/src/hamming.cpp -o bin/hamming.o 

#  kill -KILL PID
#  ps -eF
