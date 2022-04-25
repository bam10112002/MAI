#include "../include/Stoloto.h"
#include "./Sourse.h"

void FinishLotterey::operator()(Sportloto *lot, const u32 numOfTickets, const u64& fileSize)
{
    if (lot->getName() == std::string("7_49"))
    {
        finish_7_49(lot, numOfTickets, fileSize);
    }
    else
        std::cout << "lotery is not complited :(" <<std::endl;
}


void FinishLotterey::finish_7_49(Sportloto *lot, const u32 numOfTickets, const u64& fileSize)
{
    std::string basePath = "";
    json status = getStatusJson();
    nlohmann::json tickets = {};

    auto winV = static_cast<Sportloto_7_49*>(lot)->genWinVec();


    if (status[lot->getName().c_str()]["status"].get<std::string>() != std::string("start"))
    {
        //TODO: ERROR попытка завршения не начатой лотереи
    }

    int draw = status[lot->getName().c_str()]["draw"].get<int>();
    basePath = getDatasetPath() + lot->getName() + "/" + std::to_string(draw);
    // std::vector<std::thread*> thVec;
    std::thread* thVec[numOfTickets / fileSize];

    for (u32 i = 0; i <= numOfTickets / fileSize; i++)
    {
        u32 endInd = std::min(static_cast<u32>((i+1) * fileSize), numOfTickets);
        std::string path = basePath + "/" +   std::to_string(i * fileSize) + "-" + std::to_string(endInd) + ".json";
        std::ifstream inFile(path);

        thVec[i] = new std::thread(FinishLotterey::Thfinish_7_49, path, static_cast<Sportloto_7_49*>(lot), std::ref(winV));
      
        // if (!inFile.is_open())
        // {
        //     // TODO: ERROR
        // }
        // inFile >> tickets;
        // for (auto & ticket : tickets["mainVector"])
        // {
        //     static_cast<Sportloto_7_49*>(lot)->addWining(ticket, winV);
        // }
        // std::ofstream ofFile(path);
        // if (!ofFile.is_open())
        // {
        //     // TODO: ERROR
        // }
        // ofFile << tickets;
    }

    for (auto obj : thVec)
    {
        obj->join();
        delete obj;
    }
}
void FinishLotterey::Thfinish_7_49(std::string path, Sportloto_7_49* lot, const std::vector<int>& winV)
{
    nlohmann::json tickets = {};
    std::ifstream inFile(path);
    if (!inFile.is_open())
    {
        // TODO: ERROR
        std::cout << "ERROR OPEN FILE: path = " << path << std::endl;
        exit(-1);
    }
    inFile >> tickets;

    for (auto & ticket : tickets["mainVector"])
    {
        lot->addWining(ticket, winV);
    }

    std::ofstream ofFile(path);
    if (!ofFile.is_open())
    {
        // TODO: ERROR
        std::cout << "ERROR OPEN FILE: path = " << path << std::endl;
        exit(-1);
    }
    ofFile << tickets;
    ofFile.close();
    inFile.close();
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