FLAG = -Wall -Wextra -std=c++17

all: bin/simulateSale.o bin/genDraw.o bin/finishLottery.o bin/sportlotoClasses.o bin/lotery.o bin/log.o bin/find.o 
	@g++ $(FLAG) main.cpp bin/simulateSale.o bin/genDraw.o bin/finishLottery.o bin/lotery.o bin/sportlotoClasses.o bin/log.o bin/find.o  -o bin/main -pthread

bin/simulateSale.o : src/stoloto/src/simulateSale.cpp
	@g++ -c $(FLAG) src/stoloto/src/simulateSale.cpp -o bin/simulateSale.o -pthread

bin/genDraw.o : src/stoloto/src/genDraw.cpp
	@g++ -c $(FLAG) src/stoloto/src/genDraw.cpp -o bin/genDraw.o

bin/lotery.o : src/stoloto/src/lotery.cpp
	@g++ -c $(FLAG) src/stoloto/src/lotery.cpp -o bin/lotery.o

bin/sportlotoClasses.o : src/stoloto/src/sportlotoClasses.cpp
	@g++ -c $(FLAG) src/stoloto/src/sportlotoClasses.cpp -o bin/sportlotoClasses.o

bin/finishLottery.o : src/stoloto/src/finishLottery.cpp
	@g++ -c $(FLAG) src/stoloto/src/finishLottery.cpp -o bin/finishLottery.o

bin/log.o : src/stoloto/src/log.cpp src/stoloto/src/log.h
	@g++ -c $(FLAG) src/stoloto/src/log.cpp -o bin/log.o

bin/find.o : src/stoloto/src/find.cpp src/stoloto/src/find.h
	@g++ -c $(FLAG) src/stoloto/src/find.cpp -o bin/find.o

#==============================<<<<<<<<<>>>>>>>>>>=================================================

start: bin/simulateSale.o bin/genDraw.o bin/finishLottery.o bin/sportlotoClasses.o bin/lotery.o 
	@g++ $(FLAG) main.cpp bin/simulateSale.o bin/genDraw.o bin/finishLottery.o bin/lotery.o bin/sportlotoClasses.o -o bin/main -pthread
	./bin/main

test: bin/simulateSale.o bin/genDraw.o
	@g++ $(FLAG) tests/test1.cpp bin/simulateSale.o bin/genDraw.o bin/finishLottery.o -o test1 -pthread
	@./test1
	@rm test1

clear: 
	rm bin/*.o
check:
	@cppcheck -j4 --enable=performance,portability,warning,style npp.6.5.3. src/
	@cppcheck -j4 --enable=performance,portability,warning,style npp.6.5.3. main.cpp

debug: bin/simulateSale.o bin/genDraw.o bin/finishLottery.o 
	@g++ -g main.cpp bin/simulateSale.o bin/genDraw.o bin/finishLottery.o -o bin/main -pthread
rmDb:
	@rm -rf datasets/7_49/*
	@rm -rf datasets/6_45/*
	@rm -rf datasets/5_36/*
	@rm -rf datasets/4_20/*
	@echo Database is cleaned