// #include "simulateSale.h"
#include "../include/Stoloto.h"

void generateNum(const int border, std::vector<int> & vec)
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


void SimulateSale::genPackTicketsTh(Sportloto & lot, std::list<nlohmann::json> & l, u32 & currid,
std::mutex & mtx, const u32 numOfTickets)
{
    nlohmann::json ticket = {};
    u32 id;
    for (u32 i = 0; i < numOfTickets; i++)
    {
        mtx.lock();
        id = ++currid;
        mtx.unlock();

        lot.genTicket(id, ticket);
        l.push_back(ticket);
        // *saled += static_cast<int>(ticket["sale"]);
    }
}

void SimulateSale::genPackTickets(Sportloto* lot, std::list<nlohmann::json> & l, u32 & currid, const u32 numOfTickets)
{
    std::mutex mtx;
    std::list<nlohmann::json> l1, l2, l3, l4, l5;
    // int saled1 = , saled2 = 0, saled3 = 0, saled4 = 0, saled5 = 0; 

    std::thread th1(SimulateSale::genPackTicketsTh, std::ref(*lot), std::ref(l1),
                    std::ref(currid), std::ref(mtx), numOfTickets/5);
    std::thread th2(SimulateSale::genPackTicketsTh, std::ref(*lot), std::ref(l2),
                    std::ref(currid), std::ref(mtx), numOfTickets/5);
    std::thread th3(SimulateSale::genPackTicketsTh, std::ref(*lot), std::ref(l3),
                    std::ref(currid), std::ref(mtx), numOfTickets/5);
    std::thread th4(SimulateSale::genPackTicketsTh, std::ref(*lot), std::ref(l4),
                    std::ref(currid), std::ref(mtx), numOfTickets/5);
    std::thread th5(SimulateSale::genPackTicketsTh, std::ref(*lot), std::ref(l5),
                    std::ref(currid), std::ref(mtx), numOfTickets/5);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();

    l1.merge(l2);
    l1.merge(l3);
    l1.merge(l4);
    l1.merge(l5);
    l.merge(l1);

    // saled += saled1 + saled2 + saled3 + saled4 + saled5;
}

void SimulateSale::operator()(const std::string & sportloto, const u32 numOfTickets)
{
    const u32 FSize = 500000;
    Sportloto* lot = new Sportloto_7_49();
    std::string path;
    json status = getStatusJson();

    int draw = status[sportloto.c_str()]["draw"].get<int>();
    path = getDatasetPath() + sportloto + "/" + std::to_string(draw);

    u32 currid = 0;
    // u32 saled = 0;
    std::list<nlohmann::json> list;
    nlohmann::json tickets = {};

    for (u32 i = 0; i < numOfTickets / FSize; i++)
    {
        // Эмуляция продажи билетов
        currid = i * FSize;
        genPackTickets(lot, list, currid, FSize);
        tickets["mainVector"] = list;

        //Запись в файл
        std::string p2 = path + "/" +   std::to_string(i*FSize) + "-" + std::to_string((i+1)*FSize) + ".json";
        std::cout <<"create: " << p2 << std::endl;
        std::ofstream of(p2);
        of << tickets;
        // std::cout << tickets;

        // Очистка данных 
        list.clear();
        tickets.clear();
    }

    // Эмуляция продажи билетов
    currid = numOfTickets - numOfTickets % FSize;
    genPackTickets(lot, list, currid, numOfTickets % FSize);
    tickets["mainVector"] = list;

    //Запись в файл
    std::string p2 = path + "/" + std::to_string(numOfTickets - numOfTickets % FSize) + "-" + std::to_string(numOfTickets) + ".json";
    std::cout << p2 << std::endl;
    std::ofstream of(p2);
    of << tickets;

    // std::cout << "saled = " << saled << std::endl;
}



// Classes
// STOLOTO_4_20

Sportloto_4_20::Sportloto_4_20()
{
    char lotoName[] = "4_20";
    srand(time(0));
    std::ifstream fd("conf/tickets.json");
    if (!fd.is_open())
    {
        std::cout << "open file error: /conf/tickets.json" << std::endl;
        exit(-1);
    }
    json ticket = {};
    fd >> ticket;

    cost = ticket[lotoName]["cost"].get<int>();
    superPrize = ticket[lotoName]["superPrize"].get<int>();
    prizeVector = ticket[lotoName]["prize"].get<std::vector<float>>();
}
void Sportloto_4_20::genTicket(const int id, nlohmann::json & ticket)
{   
    ticket = {};
    ticket["id"] = id;
    if ((rand() % 20) == 1)
    {
        ticket["sale"] = false;
    }
    else
    {
        // генерируем числа
        std::vector<std::vector<int>> vec;
        vec.push_back(std::vector<int>());
        vec.push_back(std::vector<int>());

        for (int i = 0; i < 4; i++)
        {
            generateNum(20, vec[0]);
            generateNum(20, vec[1]);
        }

        ticket["sale"] = true;
        ticket["numbers"] = vec;
    }
}
std::pair<int,int> Sportloto_4_20::calcWin(const std::vector<std::vector<int>> & ticketVec,const std::vector<std::vector<int>> & winVec)
{
    int winCount1 = 0, winCount2 = 0;
    for (int i = 0; i < 4; i++)
    {
        if(std::find(ticketVec[0].begin(), ticketVec[0].end(), winVec[0][i]) != ticketVec[0].end())
            ++winCount1;
        if(std::find(ticketVec[1].begin(), ticketVec[1].end(), winVec[1][i]) != ticketVec[1].end())
            ++winCount2;
    }
    return std::make_pair(winCount1, winCount2);
}
bool Sportloto_4_20::addWining(json& ticket, const std::vector<std::vector<int>> & winVec)
{
    // в wining присваеваем категорию билета
    if (ticket["saled"])
    {
        std::pair<int, int> winCount = calcWin(ticket["numbers"].get<std::vector<std::vector<int>>>(), winVec);
    
        if (winCount.first == 4 || winCount.second == 4)
        {
            if (winCount.first == 4 && winCount.second == 4)
            {
                // ticket["winning"] = round(prizeVector[0] * 100) / 100;
                ticket["winning"] = 1;
                numericalPrizeVector[1] += cost;
            }
            else if (winCount.first == 3 || winCount.second == 3)
            {
                ticket["winning"] = 2;
                numericalPrizeVector[2] += cost;
            }
            else if (winCount.first == 2 || winCount.second == 2)
            {
                ticket["winning"] = 3;
                numericalPrizeVector[3] += cost;
            }
            else if (winCount.first == 1 || winCount.second == 1)
            {
                ticket["winning"] = 4;
                numericalPrizeVector[4] += cost;
            }
            else if (winCount.first == 0 || winCount.second == 0)
            {
                ticket["winning"] = 5;
                numericalPrizeVector[5] += cost;
            }
        }
        else if (winCount.first == 3 || winCount.second == 3)
        {
            if (winCount.first == 3 && winCount.second == 3)
            {
                ticket["winning"] = 6;
                numericalPrizeVector[6] += cost;
            }
            else if (winCount.first == 2 || winCount.second == 2)
            {
                ticket["winning"] = 7;
                numericalPrizeVector[7] += cost;
            }
            else if (winCount.first == 1 || winCount.second == 1)
            {
                ticket["winning"] = 8;
                numericalPrizeVector[8] += cost;
            }
            else if (winCount.first == 0 || winCount.second == 0)
            {
                ticket["winning"] = 9;
                numericalPrizeVector[9] += cost;
            }
        }
        else if (winCount.first == 2 || winCount.second == 2)
        {
            if (winCount.first == 2 && winCount.second == 2)
            {
                ticket["winning"] = 10;
                numericalPrizeVector[10] += cost;
            }
            else if (winCount.first == 1 || winCount.second == 1)
            {
                ticket["winning"] = 11;
                numericalPrizeVector[11] += cost;
            }
            else if (winCount.first == 0 || winCount.second == 0)
            {
                ticket["winning"] = 12;
                numericalPrizeVector[12] += cost;
            }
        }
        else
        {
            ticket["winning"] = 0;
        }
    }

    return false;
}
// // void Sportloto_4_20::recalcWin(json& ticket){}
// void Sportloto_4_20::recalcVec()
// {
//     for (int i = 0; i < 12; i++)
//     {
//         numericalPrizeVector[i] *= prizeVector 
//     }
// }


Sportloto_5_36::Sportloto_5_36()
{
    char lotoName[] = "5_36";
    srand(time(0));
    std::ifstream fd("conf/tickets.json");
    if (!fd.is_open())
    {
        std::cout << "open file error: /conf/tickets.json" << std::endl;
        exit(-1);
    }
    json ticket = {};
    fd >> ticket;

    cost = ticket[lotoName]["cost"].get<int>();
    superPrize = ticket[lotoName]["superPrize"].get<int>();
    prizeVector = ticket[lotoName]["prize"].get<std::vector<int>>();
}
void Sportloto_5_36::genTicket(const int id, nlohmann::json & ticket)
{
    ticket = {};
    ticket["id"] = id;
    if ((rand() % 20) == 1)
    {
        ticket["sale"] = false;
    }
    else
    {
        // генерируем числа
        std::vector<std::vector<int>> vec;
        vec.push_back(std::vector<int>());
        vec.push_back(std::vector<int>());

        for (int i = 0; i < 5; i++)
        {
            generateNum(36, vec[0]);
        }
        generateNum(4, vec[1]);

        ticket["sale"] = true;
        ticket["numbers"] = vec;
    }
}
int Sportloto_5_36::calcWin(const std::vector<std::vector<int>> & ticketVec,const std::vector<std::vector<int>> & winVec)
{
    int winCount = 0;
    for (int i = 0; i < 5; i++)
    {
        if(std::find(ticketVec[0].begin(), ticketVec[0].end(), winVec[0][i]) != ticketVec[0].end())
            ++winCount;
    }
    if (winCount == 5 && ticketVec[1][0] == winVec[1][0])
        // тк если 1 поля не хватает для суперприза то второе поле не учитывают
        ++winCount;

    return winCount;
}
bool Sportloto_5_36::addWinning(json& ticket, const std::vector<std::vector<int>> & winVec)
{
    if (ticket["saled"])
    {
        int winCount = calcWin(ticket["numbers"].get<std::vector<std::vector<int>>>(), winVec);
        if (winCount <= 5)
            ticket["winning"] = prizeVector[winCount];
        else if (winCount == 6)
        {
            ticket["winning"] = superPrize;

            return true;
            //TODO: Переписать суперприз
        }
    }

    return false;
}



Sportloto_6_45::Sportloto_6_45()
{
    char lotoName[] = "6_45";
    srand(time(0));
    std::ifstream fd("conf/tickets.json");
    if (!fd.is_open())
    {
        std::cout << "open file error: /conf/tickets.json" << std::endl;
        exit(-1);
    }
    json ticket = {};
    fd >> ticket;

    cost = ticket[lotoName]["cost"].get<int>();
    superPrize = ticket[lotoName]["superPrize"].get<int>();
    prizeVector = ticket[lotoName]["prize"].get<std::vector<int>>();
}
void Sportloto_6_45::genTicket(const int id, nlohmann::json & ticket)
{
    ticket = {};
    ticket["id"] = id;
    if ((rand() % 20) == 1)
    {
        ticket["sale"] = false;
    }
    else
    {
        // генерируем числа
        std::vector<int> vec;

        for (int i = 0; i < 6; i++)
        {
            generateNum(45, vec);
        }

        ticket["sale"] = true;
        ticket["numbers"] = vec;
    }
}
int Sportloto_6_45::calcWin(const std::vector<int> & ticketVec,const std::vector<int> & winVec)
{
    int winCount = 0;
    for (int i = 0; i < 6; i++)
    {
        if(std::find(ticketVec.begin(), ticketVec.end(), winVec[i]) != ticketVec.end())
            ++winCount;
    }
    // std::cout << winCount << std::endl;
    return winCount;
}
bool Sportloto_6_45::addWinning(json& ticket,const std::vector<int> & winVec)
{
    if (ticket["saled"])
    {
        int winCount = calcWin(ticket["numbers"].get<std::vector<int>>(), winVec);
        if (winCount <= 5)
            ticket["winning"] = prizeVector[winCount];
        else if (winCount == 6)
        {
            ticket["winning"] = superPrize;
            // std::cout << "The super prize has been played, id: " << ticket["id"] << std::endl;
            return true;
            //TODO: Переписать суперприз
        }
    }

    return false;
}


Sportloto_7_49::Sportloto_7_49()
{
    char lotoName[] = "7_49";
    srand(time(0));
    std::ifstream fd("conf/tickets.json");
    if (!fd.is_open())
    {
        std::cout << "open file error: /conf/tickets.json" << std::endl;
        exit(-1);
    }
    json ticket = {};
    fd >> ticket;

    cost = ticket[lotoName]["cost"].get<int>();
    superPrize = ticket[lotoName]["superPrize"].get<int>();
    prizeVector = ticket[lotoName]["prize"].get<std::vector<int>>();
}
void Sportloto_7_49::genTicket(const int id, nlohmann::json & ticket)
{
    ticket = {};
    ticket["id"] = id;
    if ((rand() % 20) == 1)
    {
        ticket["sale"] = false;
    }
    else
    {
        // генерируем числа
        std::vector<int> vec;

        for (int i = 0; i < 7; i++)
        {
            generateNum(49, vec);
        }

        ticket["sale"] = true;
        ticket["numbers"] = vec;
    }
}
int Sportloto_7_49::calcWin(const std::vector<int> & ticketVec,const std::vector<int> & winVec)
{
    int winCount = 0;
    for (int i = 0; i < 7; i++)
    {
        if(std::find(ticketVec.begin(), ticketVec.end(), winVec[i]) != ticketVec.end())
            ++winCount;
    }
    // std::cout << winCount << std::endl;
    return winCount;
}
bool Sportloto_7_49::addWinning(json& ticket,const std::vector<int> & winVec)
{
    if (ticket["saled"])
    {
        int winCount = calcWin(ticket["numbers"].get<std::vector<int>>(), winVec);
        if (winCount <= 6)
            ticket["winning"] = prizeVector[winCount];
        else if (winCount == 7)
        {
            ticket["winning"] = superPrize;
            // std::cout << "The super prize has been played, id: " << ticket["id"] << std::endl;
            return true;
            //TODO: Переписать суперприз
        }
    }

    return false;
}
