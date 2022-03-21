all:memory.o main.cpp
	@g++ -Wall -Werror -Wextra memory.o main.cpp -o bin/main
	@g++ -Wall -Werror -Wextra memory.o main.cpp -o .vscode/main
	@rm -rf *.o
	@echo "All compile!"
memory.o: include/Memory/memory.h include/Memory/memory.cpp
	@g++ -Wall -Werror -Wextra -c include/Memory/memory.cpp


remove: 
	@rm ./bin/*
	@rm -rf *.o
check:
	@cppcheck -j4 --enable=performance,portability,warning,style npp.6.5.3. include/
	@cppcheck -j4 --enable=performance,portability,warning,style npp.6.5.3. main.cpp
