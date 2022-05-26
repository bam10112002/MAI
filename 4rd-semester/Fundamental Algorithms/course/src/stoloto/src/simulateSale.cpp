#include "../include/Stoloto.h"

//Sourse
void generateNumbersVec(const int border, std::vector<int> & vec)
{
    bool flag = true;
    while (flag)
    {
        flag = false;
        int gen = (rand() % border) + 1;
        for (const int num : vec)
        {
            if (num == gen)
                flag = true;
        }

        if (!flag)
            vec.push_back(gen);
    }
}

std::string SimulateSale::getDatasetPath()
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
json SimulateSale::getStatusJson()
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

// Sale
void saleFile(Sportloto* lot, u32& saled, std::mutex & mtx, std::string basePath, u32 startInd, u32 endInd)
{
    u32 thSaled = 0;
    nlohmann::json tickets = {};
    std::vector<nlohmann::json> vec;

    for (u32 i = startInd; i <= endInd; ++i)
    {
        nlohmann::json ticket = {};
        thSaled += lot->genTicket(i, ticket);
        vec.push_back(ticket);
    }

    for (int i = 0; i < vec.size(); i++)
    {
        tickets["mainVector"].push_back(vec[i]);
    }
    // tickets["mainVector"] = vec;

    std::string path = basePath + "/" +   std::to_string(startInd) + "-" + std::to_string(endInd) + ".json";
    std::ofstream of(path);
    of << tickets;

    mtx.lock();
    saled += thSaled;
    mtx.unlock();

    std::cout <<"create: " << path << std::endl; //TODO: дебагерская тема в проде стоит убрать
}

u32 SimulateSale::operator()(Sportloto* lot, const u64 drawSize, const u64 Fsize)
{
    std::string basePath;
    json status = getStatusJson();
    u32 saled = 0;
    std::vector<std::thread*> thVec;
    std::mutex mtx;

    // получаем путь до паки с тиражем
    int draw = status[lot->getName().c_str()]["draw"].get<int>();
    basePath = getDatasetPath() + lot->getName() + "/" + std::to_string(draw);

    for(u32 i = 0; i <= drawSize / Fsize; i++)
    {
        u32 startInd = i*Fsize;
        u32 endInd = std::min((i+1) * Fsize, drawSize-1);

        if (thVec.size() >= 9)
        {
            for (auto obj : thVec)
            {
                obj->join();
                delete obj;
            }
            thVec.resize(0);
        }
        
        thVec.push_back(new std::thread(saleFile, lot, std::ref(saled), std::ref(mtx), basePath, startInd, endInd));
    }

    for (auto obj : thVec)
    {
        obj->join();
        delete obj;
    }

    std::cout << "Saled = " << saled << std::endl;  //TODO: дебагерская тема в проде стоит убрать
    return saled;
}
