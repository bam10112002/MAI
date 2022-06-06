#include "../include/Stoloto.h"
#include "./Sourse.h"

void FinishLotterey::operator()(Sportloto *lot, const u32 quantityOfTickets, const u64& fileSize, const u64& income)
{
    u32 AmountOfWinings = 0;
    if (lot->getName() == std::string("7_49"))
    {
        AmountOfWinings = finish_7_49(lot, quantityOfTickets, fileSize, fileMtx);
    }
    else if (lot->getName() == std::string("6_45"))
    {
        AmountOfWinings = finish_6_45(lot, quantityOfTickets, fileSize, fileMtx);
    }
    else if (lot->getName() == std::string("5_36"))
    {
        AmountOfWinings = finish_5_36(lot, quantityOfTickets, fileSize, fileMtx);
    }
    // else if (lot->getName() == std::string("4_20"))
    // {
    //     AmountOfWinings = finish_4_20(lot, quantityOfTickets, fileSize);
    // }
    else
        std::cout << "lotery is not complited :(" <<std::endl;

    std::cout << "Income = "<<income << std::endl;
    std::cout << "Amount Of Winings = "<< AmountOfWinings << std::endl;
    // std::cout << "Test = " << this->GetSuperPrize(lot, fileMtx) << std::endl;
    this->SetNewSuperPrize(lot, income - AmountOfWinings, fileMtx);
}

u32 FinishLotterey::finish_7_49(Sportloto *lot, const u32 quantityOfTickets, const u64& fileSize, std::mutex& fileMtx)
{
    std::string basePath = "";
    json status = getStatusJson();
    nlohmann::json tickets = {};

    auto winV = static_cast<Sportloto_7_49*>(lot)->genWinVec();
    int draw = status[lot->getName().c_str()]["draw"].get<int>();
    basePath = getDatasetPath() + lot->getName() + "/" + std::to_string(draw);

    // TODO: Debug убрать
    std::cout << "WIN vector:  ";
    for (auto num : winV)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    //TODO: Убрать в клвсс Log
    json j= {};
    std::ifstream ifs(basePath+"/log.json");
    ifs >> j;
    j["winVector"] = winV;
    std::ofstream of(basePath+"/log.json");
    of << j;
    of.close();
    ifs.close();

    if (status[lot->getName().c_str()]["status"].get<std::string>() != std::string("start"))
    {
        //TODO: ERROR попытка завршения не начатой лотереи
    }

    std::vector<std::thread*> thVec;
    u32 AmountOfWinings = 0;
    std::mutex mtx;

    for (u32 i = 0; i <= quantityOfTickets / fileSize; i++)
    {
        u32 startInd = i * fileSize;
        u32 endInd = std::min(static_cast<u32>((i+1) * fileSize), quantityOfTickets)-1;
        std::string path = basePath + "/" +   std::to_string(startInd) + "-" + std::to_string(endInd) + ".json";
        std::cout << "path: " << path << std::endl;
        std::ifstream inFile(path);

        if (thVec.size() >= 9)
        {
            // std::cout <<" free treads" << std::endl;
            for (auto obj : thVec)
            {
                obj->join();
                delete obj;
            }
            thVec.resize(0);
            std::cout << "completed  " << i << " / " << quantityOfTickets / fileSize << std::endl;
        }

        thVec.push_back(new std::thread(FinishLotterey::Thfinish_7_49, path, static_cast<Sportloto_7_49*>(lot),
         std::ref(winV), std::ref(mtx), std::ref(AmountOfWinings), std::ref(fileMtx)));
    }

    for (auto obj : thVec)
    {
        obj->join();
        delete obj;
    }
    //TODO: Убрать в клвсс Log
    j= {};
    ifs.open(basePath+"/log.json");
    ifs >> j;
    j["AmountOfWinings"] = AmountOfWinings;
    of.open(basePath+"/log.json");
    of << j;
    of.close();
    ifs.close(); 
    return AmountOfWinings;
}
void FinishLotterey::Thfinish_7_49(std::string path, Sportloto_7_49* lot, const std::vector<int>& winV, std::mutex & mtx, u32& AmWinings, std::mutex& fileMtx)
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

    u32 amountOfWinnings = 0;
    for (auto & ticket : tickets["mainVector"])
    {
        if (lot->addWining(ticket, winV))
        {
            ticket["winning"] = GetSuperPrize(lot, fileMtx);
            std::cout << "The super prize was played!!! WHeeeeeeee)" << std::endl;
            std::cout << "winner's id = " << ticket["id"] << std::endl;
        }
        if (ticket["saled"])
            amountOfWinnings += ticket["winning"].get<int>();
    }
    // std::cout << "Amount Of Winnings = " << amountOfWinnings << std::endl;
    mtx.lock();
    AmWinings += amountOfWinnings;
    mtx.unlock();

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

u32 FinishLotterey::finish_6_45(Sportloto *lot, const u32 quantityOfTickets, const u64& fileSize, std::mutex& fileMtx)
{
    std::string basePath = "";
    json status = getStatusJson();

    if (status[lot->getName().c_str()]["status"].get<std::string>() != std::string("start"))
    {
        //TODO: ERROR попытка завршения не начатой лотереи
    }
    
    nlohmann::json tickets = {};
    int draw = status[lot->getName().c_str()]["draw"].get<int>();
    basePath = getDatasetPath() + lot->getName() + "/" + std::to_string(draw);

    auto winV = static_cast<Sportloto_6_45*>(lot)->genWinVec();
    std::mutex mtx;
    u32 AmountOfWining = 0;

    // TODO: Debug убрать
    std::cout << "WIN vector:  ";
    for (auto num : winV)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    //TODO: Убрать в клвсс Log
    json j= {};
    std::ifstream ifs(basePath+"/log.json");
    ifs >> j;
    j["winVector"] = winV;
    std::ofstream of(basePath+"/log.json");
    of << j;
    of.close();
    ifs.close();

    std::vector<std::thread*> thVec;

    for (u32 i = 0; i <= quantityOfTickets / fileSize; i++)
    {
        u32 startInd = i * fileSize;
        u32 endInd = std::min(static_cast<u32>((i+1) * fileSize), quantityOfTickets)-1;
        std::string path = basePath + "/" +   std::to_string(startInd) + "-" + std::to_string(endInd) + ".json";
        std::ifstream inFile(path);

        if (thVec.size() >= 9)
        {
            // std::cout <<" free treads" << std::endl;
            for (auto obj : thVec)
            {
                obj->join();
                delete obj;
            }
            thVec.resize(0);
            std::cout << "completed  " << i << " / " << quantityOfTickets / fileSize << std::endl;
        }

        thVec.push_back(new std::thread(FinishLotterey::Thfinish_6_45, path, static_cast<Sportloto_6_45*>(lot),
                        std::ref(winV), std::ref(mtx), std::ref(AmountOfWining), std::ref(fileMtx)));
    }

    for (auto obj : thVec)
    {
        obj->join();
        delete obj;
    }

    //TODO: Убрать в клвсс Log
    j= {};
    ifs.open(basePath+"/log.json");
    ifs >> j;
    j["AmountOfWinings"] = AmountOfWining;
    of.open(basePath+"/log.json");
    of << j;
    of.close();
    ifs.close(); 
    return AmountOfWining;
}
void FinishLotterey::Thfinish_6_45(std::string path, Sportloto_6_45* lot, const std::vector<int>& winV, std::mutex & mtx, u32& AmWinings, std::mutex& fileMtx)
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

    u32 amountOfWinnings = 0;
    for (auto & ticket : tickets["mainVector"])
    {
        if (lot->addWining(ticket, winV))
        {
            ticket["winning"] = GetSuperPrize(lot, fileMtx);
            std::cout << "The super prize was played!!! WHeeeeeeee)" << std::endl;
            std::cout << "winner's id = " << ticket["id"] << std::endl;
        }
        if (ticket["saled"])
            amountOfWinnings += ticket["winning"].get<int>();
    }
    // std::cout << "Amount Of Winnings = " << amountOfWinnings << std::endl;
    mtx.lock();
    AmWinings += amountOfWinnings;
    mtx.unlock();

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


u32 FinishLotterey::finish_5_36(Sportloto *lot, const u32 quantityOfTickets, const u64& fileSize, std::mutex& fileMtx)
{
    std::string basePath = "";
    json status = getStatusJson();
    nlohmann::json tickets = {};

    int draw = status[lot->getName().c_str()]["draw"].get<int>();
    basePath = getDatasetPath() + lot->getName() + "/" + std::to_string(draw);
    auto winV = static_cast<Sportloto_5_36*>(lot)->genWinVec();
    u32 AmountOfWining = 0;
    std::mutex mtx;

    // TODO: Debug убрать
    std::cout << "WIN vector:  ";
    for (auto vv : winV)
    {
        for (auto num : vv)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl << "             ";
    }
    std::cout << std::endl;

    //TODO: Убрать в клвсс Log
    json j= {};
    std::ifstream ifs(basePath+"/log.json");
    ifs >> j;
    j["winVector"] = winV;
    std::ofstream of(basePath+"/log.json");
    of << j;
    of.close();
    ifs.close();


    if (status[lot->getName().c_str()]["status"].get<std::string>() != std::string("start"))
    {
        //TODO: ERROR попытка завршения не начатой лотереи
    }

    std::vector<std::thread*> thVec;

    for (u32 i = 0; i <= quantityOfTickets / fileSize; i++)
    {
        u32 startInd = i * fileSize;
        u32 endInd = std::min(static_cast<u32>((i+1) * fileSize), quantityOfTickets)-1;
        std::string path = basePath + "/" +   std::to_string(startInd) + "-" + std::to_string(endInd) + ".json";
        std::ifstream inFile(path);

        if (thVec.size() >= 9)
        {
            // std::cout <<" free treads" << std::endl;
            for (auto obj : thVec)
            {
                obj->join();
                delete obj;
            }
            thVec.resize(0);
            std::cout << "completed  " << i << " / " << quantityOfTickets / fileSize << std::endl;
        }

        thVec.push_back(new std::thread(FinishLotterey::Thfinish_5_36, path, static_cast<Sportloto_5_36*>(lot), 
                                        std::ref(winV), std::ref(mtx), std::ref(AmountOfWining), std::ref(fileMtx)));
    }

    for (auto obj : thVec)
    {
        obj->join();
        delete obj;
    }

    std::cout << "Amount Of Winnings = " << AmountOfWining << std::endl; //TODO: Debug
    //TODO: Убрать в клвсс Log
    j= {};
    ifs.open(basePath+"/log.json");
    ifs >> j;
    j["AmountOfWinings"] = AmountOfWining;
    of.open(basePath+"/log.json");
    of << j;
    of.close();
    ifs.close(); 
    return AmountOfWining;
}
void FinishLotterey::Thfinish_5_36(std::string path, Sportloto_5_36* lot, const std::vector<std::vector<int>>& winV, std::mutex & mtx, u32& AmWinings, std::mutex& fileMtx)
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

    u32 amountOfWinnings = 0;
    for (auto & ticket : tickets["mainVector"])
    {
        if (lot->addWining(ticket, winV))
        {
            ticket["winning"] = GetSuperPrize(lot, fileMtx);
            std::cout << "The super prize was played!!! WHeeeeeeee)" << std::endl;
            std::cout << "winner's id = " << ticket["id"] << std::endl;
        }
        if (ticket["saled"])
            amountOfWinnings += ticket["winning"].get<int>();
    }
    // std::cout << "Amount Of Winnings = " << amountOfWinnings << std::endl;
    mtx.lock();
    AmWinings += amountOfWinnings;
    mtx.unlock();


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

u32 FinishLotterey::finish_4_20(Sportloto *lot, const u32 quantityOfTickets, const u64& fileSize)
{
    std::string basePath = "";
    json status = getStatusJson();
    nlohmann::json tickets = {};

    int draw = status[lot->getName().c_str()]["draw"].get<int>();
    basePath = getDatasetPath() + lot->getName() + "/" + std::to_string(draw);
    auto winV = static_cast<Sportloto_4_20*>(lot)->genWinVec();
    u32 AmountOfWining = 0;
    std::mutex mtx;

    // TODO: Debug убрать
    std::cout << "WIN vector:  ";
    for (auto vv : winV)
    {
        for (auto num : vv)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl << "             ";
    }
    std::cout << std::endl;

    //TODO: Убрать в клвсс Log
    json j= {};
    std::ifstream ifs(basePath+"/log.json");
    ifs >> j;
    j["winVector"] = winV;
    std::ofstream of(basePath+"/log.json");
    of << j;
    of.close();
    ifs.close();


    if (status[lot->getName().c_str()]["status"].get<std::string>() != std::string("start"))
    {
        //TODO: ERROR попытка завршения не начатой лотереи
    }

    std::vector<std::thread*> thVec;

    for (u32 i = 0; i <= quantityOfTickets / fileSize; i++)
    {
        // std::cout << "OK";
        u32 startInd = i * fileSize;
        u32 endInd = std::min(static_cast<u32>((i+1) * fileSize), quantityOfTickets)-1;
        std::string path = basePath + "/" +   std::to_string(startInd) + "-" + std::to_string(endInd) + ".json";
        // std::cout << "path" << path << std::endl;
        std::ifstream inFile(path);

        Thfinish_4_20(path, static_cast<Sportloto_4_20*>(lot), winV, mtx, AmountOfWining);
    }

    // static_cast<Sportloto_4_20*>(lot)->recalckPrizeVec(PrizeBanck);

    // for (u32 i = 0; i < quantityOfTickets / fileSize; i++)
    // {
    //     u32 startInd = i * fileSize;
    //     u32 endInd = std::min(static_cast<u32>((i+1) * fileSize), quantityOfTickets)-1;
    //     std::string path = basePath + "/" +   std::to_string(startInd) + "-" + std::to_string(endInd) + ".json";
    //     std::ifstream inFile(path);

    //     if (thVec.size() >= 9)
    //     {
    //         // std::cout <<" free treads" << std::endl;
    //         for (auto obj : thVec)
    //         {
    //             obj->join();
    //             delete obj;
    //         }
    //         thVec.resize(0);
    //         std::cout << "completed  " << i << " / " << quantityOfTickets / fileSize << std::endl;
    //     }

    //     thVec.push_back(new std::thread(FinishLotterey::Thfinish_4_20, path, static_cast<Sportloto_4_20*>(lot), 
    //                                     std::ref(winV), std::ref(mtx), std::ref(AmountOfWining)));
    // }

    // for (auto obj : thVec)
    // {
    //     obj->join();
    //     delete obj;
    // }

    // std::cout << "Amount Of Winnings = " << AmountOfWining << std::endl; //TODO: Debug
    // //TODO: Убрать в клвсс Log
    // j= {};
    // ifs.open(basePath+"/log.json");
    // ifs >> j;
    // j["AmountOfWinings"] = AmountOfWining;
    // of.open(basePath+"/log.json");
    // of << j;
    // of.close();
    // ifs.close(); 
    // return AmountOfWining;
}
void FinishLotterey::Thfinish_4_20(std::string path, Sportloto_4_20* lot, const std::vector<std::vector<int>>& winV, std::mutex & mtx, u32&)
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

    // std::cout << "good" << std::endl;
    u32 amountOfWinnings = 0;
    for (auto & ticket : tickets["mainVector"])
    {
        lot->addWining(ticket, winV);
        // std::cout << ticket["wining"];
        // if (ticket["saled"])
        //     amountOfWinnings += ticket["winning"].get<int>();
    }
    // std::cout << "Amount Of Winnings = " << amountOfWinnings << std::endl;
    // mtx.lock();
    // AmWinings += amountOfWinnings;
    // mtx.unlock();


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
void Thfinish_rec_4_20(std::string path, Sportloto_4_20* lot, std::mutex & mtx, u32& AmWinings)
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

    u32 amountOfWinnings = 0;
    for (auto & ticket : tickets["mainVector"])
    {
        lot->recalckWin(ticket);
        if (ticket["saled"])
            amountOfWinnings += ticket["winning"].get<int>();
    }
    // std::cout << "Amount Of Winnings = " << amountOfWinnings << std::endl;
    mtx.lock();
    AmWinings += amountOfWinnings;
    mtx.unlock();


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
int FinishLotterey::GetSuperPrize(Sportloto* lot,std::mutex& fileMtx)
{
    int Superprize;
    std::fstream fs("./conf/tickets.json");
    json ticketsInfo = {};

    fileMtx.lock();
    fs >> ticketsInfo;
    Superprize = ticketsInfo[lot->getName()]["superPrize"].get<int>();
    ticketsInfo[lot->getName()]["superPrize"] = PrizeBanck;
    fs.close();
    fs.open("./conf/tickets.json", std::ios::out);
    fs << ticketsInfo;
    fileMtx.unlock();
    
    return Superprize;
}
void FinishLotterey::SetNewSuperPrize(Sportloto* lot, int delta, std::mutex& fileMtx)
{
    int Superprize;
    std::fstream fs("./conf/tickets.json",std::ios::in);
    json ticketsInfo = {};

    fileMtx.lock();
    fs >> ticketsInfo;
    Superprize = ticketsInfo[lot->getName()]["superPrize"].get<int>();
    std::cout << "Super = " << Superprize << std::endl;
    ticketsInfo[lot->getName()]["superPrize"] = std::max(Superprize + delta, PrizeBanck);

    fs.close();
    fs.open("./conf/tickets.json", std::ios::out);
    fs << ticketsInfo;
    fileMtx.unlock();
}
