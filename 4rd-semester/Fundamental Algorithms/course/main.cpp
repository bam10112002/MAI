#include "src/stoloto/src/genDraw.h"
#include "src/stoloto/src/simulateSale.h"
#include "src/stoloto/src/finishLottery.h"
using namespace std;


int main()
{
    std::string lot = "7_49";
    std::string p = gendraw(std::string(lot));
    simulateSale(p, 2000000);
    finishLottery(std::string(lot));

    return 0;
}