// #include "src/stoloto/src/genDraw.h"
// #include "src/stoloto/src/simulateSale.h"
// #include "src/stoloto/src/finishLottery.h"
#include "src/stoloto/include/Stoloto.h"
#include "src/stoloto/src/find.h"

using namespace std;

void FoundByWinig(Sportloto*);
void FoundById(Sportloto*);

int main()
{
    Sportloto* lot = new Sportloto_6_45; 
    Lottery lottery(lot, 30);

    uint64_t time2;
    auto start = std::chrono::high_resolution_clock::now();

    lottery.GenDraw();
    lottery.SimSale();
    lottery.FinishLottery();
    // FoundById(lot);
    // FoundByWinig(lot);

    time2 = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::high_resolution_clock::now()-start).count();
    std::cout << "Work time = " << time2  << " milsec" << std::endl;



    delete lot;

   return 0;
}

void FoundByWinig(Sportloto* lot)
{
    Find find;
    std::cout << "\n" << "Found tickets with a win equal to 30: " <<std::endl;
    std::vector<json> vec = find.FindTicketsByWinig(lot, 13, 30);
    for (auto obj : vec)
    {
        std::cout << obj << std::endl;
    }
    std::cout << "\n" << "Found tickets with a win equal to 100: " <<std::endl;
    std::vector<json> vec2 = find.FindTicketsByWinig(lot, 13, 100);
    for (auto obj : vec2)
    {
        std::cout << obj << std::endl;
    }
}
void FoundById(Sportloto* lot)
{
    Find find;
    std::cout << "\n\n" << "Finded ticket with id = 26: " 
        << find.FindTicketById(lot, 13, 26) << std::endl;
    std::cout << "" << "Finded ticket with id = 7: "
         << find.FindTicketById(lot, 13, 7) << std::endl;
}
