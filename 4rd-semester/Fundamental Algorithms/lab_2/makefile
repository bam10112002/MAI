FLAG = -O2 -Wall -Wextra -std=c++17
all:memory.o exeptions.o main.cpp
	@g++ $(FLAG) memory.o exeptions.o main.cpp -o bin/main
	@rm -rf *.o
	@echo "all compile!"
	@echo "main file added to bin/"

memory.o: src/Memory/memory.h src/Memory/memory.cpp
	@g++ $(FLAG) -c src/Memory/memory.cpp
exeptions.o: src/Exeptions/exeptions.h src/Exeptions/exeptions.cpp
	@g++ $(FLAG) -c src/Exeptions/exeptions.cpp

test:memory.o main.cpp
	@g++ -O2 -std=c++17 memory.o main.cpp -o bin/main
	@rm -rf *.o
	@echo "all compile!"
	@echo "main file added to bin/"

remove: 
	@rm ./bin/*
	@rm -rf *.o
check:
	@cppcheck -j4 --enable=performance,portability,warning,style npp.6.5.3. src/
	@cppcheck -j4 --enable=performance,portability,warning,style npp.6.5.3. main.cpp

gdb: 
	@g++ -g -c src/Memory/memory.cpp
	@g++ -g memory.o main.cpp -o bin/main
	@rm -rf *.o
	gdb bin/main
	layout next
valgrind: memory.o exeptions.o main.cpp
	g++ -O0 -g memory.o exeptions.o main.cpp -o bin/main
	valgrind --leak-check=full --track-origins=yes ./bin/main
