// #include "src/stoloto/src/genDraw.h"
// #include "src/stoloto/src/simulateSale.h"
// #include "src/stoloto/src/finishLottery.h"
#include "src/stoloto/include/Stoloto.h"

using namespace std;


int main()
{
    std::string lot = "7_49";
    Lottery lottery;

    uint64_t time2;
    auto start = std::chrono::high_resolution_clock::now();
    lottery.genDraw(lot);
    lottery.sale(lot, 6000000);
    time2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count();
    std::cout << "Time = " << time2  << std::endl;


    // std::string lot2 = "6_45";
    start = std::chrono::high_resolution_clock::now();
    lottery.genDraw(lot);
    lottery.sale(lot, 6000000);
    time2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count();
    std::cout << "Time = " << time2  << std::endl;

    return 0;
}