#include "../include/Stoloto.h"


Lottery::Lottery(Sportloto* _lot, u64 _drawSize)
{
    lot = _lot;
    drawSize = _drawSize;
    saled = 0;
    fileSize = static_cast<u64>(FS);
}

void Lottery::GenDraw()
{
    genDraw(lot->getName());
}
void Lottery::SimSale()
{
    saled = sale(lot, drawSize, fileSize);
}
void Lottery::FinishLottery()
{
    finish(lot, drawSize, fileSize, lot->Cost()*saled);
}
