// #include "src/stoloto/src/genDraw.h"
// #include "src/stoloto/src/simulateSale.h"
// #include "src/stoloto/src/finishLottery.h"
#include "src/stoloto/include/Stoloto.h"

using namespace std;


int main()
{
    std::string lot = "7_49";
    Lottery lottery;

    lottery.genDraw(lot);
    lottery.sale(lot, 300);

    return 0;
}