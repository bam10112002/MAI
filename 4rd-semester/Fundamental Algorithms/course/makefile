FLAG = -O2 -Wall -Wextra -std=c++17

all: bin/simulateSale.o bin/genDraw.o bin/finishLottery.o 
	@g++ $(FLAG) -Werror main.cpp bin/simulateSale.o bin/genDraw.o bin/finishLottery.o -o bin/main -pthread

bin/simulateSale.o : src/stoloto/src/simulateSale.cpp
	@g++ -c $(FLAG) src/stoloto/src/simulateSale.cpp -o bin/simulateSale.o -pthread

bin/genDraw.o : src/stoloto/src/genDraw.cpp
	@g++ -c $(FLAG) src/stoloto/src/genDraw.cpp -o bin/genDraw.o

bin/finishLottery.o : src/stoloto/src/finishLottery.cpp
	@g++ -c $(FLAG) src/stoloto/src/finishLottery.cpp -o bin/finishLottery.o

#==============================<<<<<<<<<>>>>>>>>>>=================================================

test: bin/simulateSale.o bin/genDraw.o
	@g++ $(FLAG) tests/test1.cpp bin/simulateSale.o bin/genDraw.o bin/finishLottery.o -o test1 -pthread
	@./test1
	@rm test1

clear: 
	rm bin/*.o
check:
	@cppcheck -j4 --enable=performance,portability,warning,style npp.6.5.3. src/
	@cppcheck -j4 --enable=performance,portability,warning,style npp.6.5.3. main.cpp