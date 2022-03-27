FLAG = -O2 -Wall -Wextra -std=c++17

all: bin/simulateSale.o bin/genDraw.o bin/finishLottery.o 
	g++ $(FLAG) main.cpp bin/simulateSale.o bin/genDraw.o bin/finishLottery.o -o bin/main -pthread

bin/simulateSale.o : src/stoloto/src/simulateSale.cpp src/stoloto/src/simulateSale.h
	g++ -c $(FLAG)  src/stoloto/src/simulateSale.cpp -o bin/simulateSale.o -pthread
bin/genDraw.o : src/stoloto/src/genDraw.cpp src/stoloto/src/genDraw.h
	g++ -c $(FLAG) src/stoloto/src/genDraw.cpp -o bin/genDraw.o
bin/finishLottery.o : src/stoloto/src/finishLottery.cpp src/stoloto/src/finishLottery.h
	g++ -c $(FLAG)  src/stoloto/src/finishLottery.cpp -o bin/finishLottery.o

clean: 
	rm bin/*.o
test: bin/simulateSale.o bin/genDraw.o
	g++ $(FLAG) main.cpp bin/simulateSale.o bin/genDraw.o bin/finishLottery.o -o bin/main -pthread
	./bin/main