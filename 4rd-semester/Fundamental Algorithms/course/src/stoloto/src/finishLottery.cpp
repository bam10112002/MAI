#include "../include/Stoloto.h"
#include "./Sourse.h"

void FinishLotterey::operator()(Sportloto *lot, const u32 numOfTickets)
{
    // const u32 FSize = 500000;
    // std::string path = "";
    // json status = getStatusJson();
    // nlohmann::json tickets = {};

    // if (lot->getName() == "6_45" || lot->getName() == "7_49")
    // {
    //     auto winV = lot->genWinVec();
    // }


    // if (status[lot->getName().c_str()]["status"].get<std::string>() == std::string("start"))
    // {
    //     int draw = status[lot->getName().c_str()]["draw"].get<int>();
    //     path = getDatasetPath() + lot->getName() + "/" + std::to_string(draw);

    //     for (u32 i = 0; i < numOfTickets / FSize; i++)
    //     {
    //         std::string p2 = path + "/" + std::to_string(i * FSize) + "-" + std::to_string((i + 1) * FSize) + ".json";
    //         std::ifstream inf(p2);
    //         inf >> tickets;

    //         // итерируемся пл массиву билетов
    //         for (auto & item : tickets["mainVector"])
    //         {
    //             lot->addWining(item, winV);
    //         }

    //         //Запись в файл тот же json файл
    //         std::ofstream of(p2);
    //         of << tickets;

    //         tickets.clear();
    //     }


    //     std::string p2 = path + "/" + std::to_string(numOfTickets - numOfTickets % FSize) + "-" + std::to_string(numOfTickets) + ".json";
    //     std::ifstream inf(p2);
    //     inf >> tickets;
    //     // итерируемся пл массиву билетов
    //     for (auto & item : tickets["mainVector"])
    //     {
    //         lot->addWining(item, winV);
    //     }

    //     //Запись в файл тот же json файл
    //     std::ofstream of(p2);
    //     of << tickets;
    // }
    // else
    // {
    //     // TODO: trow LotteryError;
    //     std::cout << "error draw sale is not started please start loterey" << std::endl;
    //     exit(-1);
    // }
    // // return path;
}


//Sourse
std::string FinishLotterey::getDatasetPath()
{
    json datasetPath = {};
    std::ifstream fd2("conf/path.json");
    if (!fd2.is_open())
    {
        std::cout << "open file error: /conf/path.json" << std::endl;
        exit(-1);
    }
    fd2 >> datasetPath;
    return datasetPath["dataset"].get<std::string>();
}
json FinishLotterey::getStatusJson()
{
    std::ifstream fd("conf/status.json");
    if (!fd.is_open())
    {
        std::cout << "open file error: /conf/path.json" << std::endl;
        exit(-1);
    }
    json status = {};
    fd >> status;
    return status;
}