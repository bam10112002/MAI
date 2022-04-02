FLAG = -O2 -Wall -Werror -Wextra -std=c++17
all:memory.o main.cpp
	@g++ $(FLAG) memory.o main.cpp -o bin/main
	@rm -rf *.o
	@echo "all compile!"
	@echo "main file added to bin/"

memory.o: src/Memory/memory.h src/Memory/memory.cpp
	@g++ $(FLAG) -c src/Memory/memory.cpp


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
	@g++ -c src/Memory/memory.cpp
	@g++ -g memory.o main.cpp -o bin/main
	@rm -rf *.o
	gdb bin/main
	layout next
