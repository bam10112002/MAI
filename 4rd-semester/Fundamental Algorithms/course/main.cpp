// #include "src/stoloto/src/genDraw.h"
// #include "src/stoloto/src/simulateSale.h"
// #include "src/stoloto/src/finishLottery.h"
#include "src/stoloto/include/Stoloto.h"

using namespace std;


int main()
{
    Sportloto* lot = new Sportloto_7_49; 
    Lottery lottery(lot, 1000000);

    uint64_t time2;
    auto start = std::chrono::high_resolution_clock::now();

    lottery.GenDraw();
    lottery.SimSale();
    lottery.FinishLottery();

    time2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count();
    std::cout << "Sale time = " << time2  << " milsec" << std::endl;

    return 0;
}