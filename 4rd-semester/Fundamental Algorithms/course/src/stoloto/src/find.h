#ifndef FIND_H
#define FIND_H
#include "../include/Stoloto.h"
#include <string>
#include <algorithm>

class Find
{
private:

public:
    json FindTicketById(Sportloto* lot, int draw, int id)
    {  
        std::string path = "./datasets/" + lot->getName() + "/" + std::to_string(draw);
        std::fstream ifs(path + "/log.json");
        nlohmann::json log = {};

        ifs >> log;
        int drawSize = log["drawSize"].get<int>();
        int fileSize = log["fileSize"].get<int>();

        if (id > drawSize || id < 0)
        {
            std::cout << "error id unvalid: id = " << id << " Draw Size = " << drawSize ;
            return json();
        }
        u32 startInd = id - id % fileSize;
        u32 endInd = std::min((startInd + fileSize)-1, static_cast<u32>(drawSize-1));

        std::fstream ticketsFile(path + "/" + std::to_string(startInd) + "-" + std::to_string(endInd) + ".json");
        if (!ticketsFile)
        {
            std::cout << "Find by id: Error open file";
            return json();
        }
        else
        {
            json tickets = {};
            ticketsFile >> tickets;
            // std::cout << tickets;

            for (const auto& ticket : tickets["mainVector"])
            {
                if (ticket["id"].get<int>() == id)
                {
                    // std::cout << ticket;
                    return ticket;
                }
            }
        }
    }
    static std::vector<json> FindTicketsByWinig(Sportloto* lot, int draw, int wining)
    {
        std::vector<json> rez;
        // конструируем путь до папки тиража 
        std::string basePath = "./datasets/" + lot->getName() + "/" + std::to_string(draw);

        // Получаем лог тиража
        std::fstream fs(basePath + "/log.json");
        nlohmann::json log = {};
        fs >> log;
        int drawSize = log["drawSize"].get<int>();
        int fileSize = log["fileSize"].get<int>();

        // итерируемся по всему тиражу
        for(u32 i = 0; i <= drawSize / fileSize; i++)
        {
            nlohmann::json tickets = {};
            // собираем путь до файла
            u32 startInd = i*fileSize;
            u32 endInd = std::min((i+1) * fileSize, static_cast<u32>(drawSize))-1;
            std::string path = basePath + "/" +   std::to_string(startInd) + "-" + std::to_string(endInd) + ".json";

            std::fstream ticketFile(path);
            // std::cout << path <<std::endl;
            if (!ticketFile)
            {
                std::cout << "Find by win: Error open file"<<std::endl;
                return rez;
            }
            else
            {
                ticketFile >> tickets;
                // std::cout << tickets;
                for (auto& ticket : tickets["mainVector"])
                {
                    // std::cout << ticket <<std::endl;
                    if (ticket["saled"].get<bool>() != false)
                    {
                        // std::cout << ticket["id"].get<int>() << " win = "  << ticket["saled"].get<bool>() << std::endl;
                        if (ticket["winning"].get<int>() == wining)
                        {
                            rez.push_back(ticket);
                        }
                    }
                }
            }
        }
        return rez;
    }
};

#endif