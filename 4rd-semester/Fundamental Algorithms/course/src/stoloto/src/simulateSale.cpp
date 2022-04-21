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

//Loterey
Lottery::Lottery(Sportloto* _lot, u64 _drawSize)
{
    lot = _lot;
    drawSize = _drawSize;
    saled = 0;
    fileSize = static_cast<u16>(500000);
}

void Lottery::GenDraw()
{
    genDraw(lot->getName());
}
void Lottery::SimSale()
{
    saled = sale(lot, drawSize, fileSize);
}
void Lottery::FinishLottery(){}

void SimulateSale::genPackTicketsTh(Sportloto & lot, std::list<nlohmann::json> & l, u32 & currid,
std::mutex & mtx, const u64 numOfTickets, u32 & saled)
{
    nlohmann::json ticket = {};
    u32 id;
    for (u32 i = 0; i < numOfTickets; i++)
    {
        mtx.lock();
        id = ++currid;
        mtx.unlock();

        saled += lot.genTicket(id, ticket);
        l.push_back(ticket);
    }
}

u32 SimulateSale::genPackTickets(Sportloto* lot, std::list<nlohmann::json> & l, u32 & currid, const u32 numOfTickets)
{
    std::mutex mtx;
    std::list<nlohmann::json> l1, l2, l3, l4, l5;
    u32 saled1 = 0, saled2 = 0, saled3 = 0, saled4 = 0, saled5 = 0; 

    std::thread th1(SimulateSale::genPackTicketsTh, std::ref(*lot), std::ref(l1),
                    std::ref(currid), std::ref(mtx), numOfTickets/5, std::ref(saled1));
    std::thread th2(SimulateSale::genPackTicketsTh, std::ref(*lot), std::ref(l2),
                    std::ref(currid), std::ref(mtx), numOfTickets/5, std::ref(saled2));
    std::thread th3(SimulateSale::genPackTicketsTh, std::ref(*lot), std::ref(l3),
                    std::ref(currid), std::ref(mtx), numOfTickets/5, std::ref(saled3));
    std::thread th4(SimulateSale::genPackTicketsTh, std::ref(*lot), std::ref(l4),
                    std::ref(currid), std::ref(mtx), numOfTickets/5, std::ref(saled4));
    std::thread th5(SimulateSale::genPackTicketsTh, std::ref(*lot), std::ref(l5),
                    std::ref(currid), std::ref(mtx), numOfTickets/5, std::ref(saled5));
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

    return (saled1 + saled2 + saled3 + saled4 + saled5);
}

u32 SimulateSale::operator()(Sportloto* lot, const u64 drawSize, const u64 Fsize)
{
    std::string basePath;
    json status = getStatusJson();
    u32 currid = 0;
    u32 saled = 0;

    int draw = status[lot->getName().c_str()]["draw"].get<int>();
    basePath = getDatasetPath() + lot->getName() + "/" + std::to_string(draw);


    std::list<nlohmann::json> list;
    nlohmann::json tickets = {};

    for(u32 i = 0; i <= drawSize / Fsize; i++)
    {
        u32 endInd = std::min((i+1) * Fsize, drawSize);
        saled += genPackTickets(lot, list, currid, endInd - currid);
        tickets["mainVector"] = list;

        // Запись проданных билетов в файл
        std::string path = basePath + "/" +   std::to_string(i * Fsize) + "-" + std::to_string(endInd) + ".json";
        std::ofstream of(path);
        of << tickets;
        std::cout <<"create: " << path << std::endl; //TODO: дебагерская тема в проде стоит убрать

        // Очистка данных 
        list.clear();
        tickets.clear();
    }

    // std::cout << "saled = " << saled << std::endl;
    return saled;
}



// Classes
Sportloto_4_20::Sportloto_4_20()
{
    wins = 0;
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
std::string Sportloto_4_20::getName() const
{
    return std::string("4_20");
}
bool Sportloto_4_20::genTicket(const int id, nlohmann::json & ticket)const
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
    return ticket["sale"];
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
                numericalPrizeVector[1] += 1;
            }
            else if (winCount.first == 3 || winCount.second == 3)
            {
                ticket["winning"] = 2;
                numericalPrizeVector[2] += 1;
            }
            else if (winCount.first == 2 || winCount.second == 2)
            {
                ticket["winning"] = 3;
                numericalPrizeVector[3] += 1;
            }
            else if (winCount.first == 1 || winCount.second == 1)
            {
                ticket["winning"] = 4;
                numericalPrizeVector[4] += 1;
            }
            else if (winCount.first == 0 || winCount.second == 0)
            {
                ticket["winning"] = 5;
                numericalPrizeVector[5] += 1;
            }
        }
        else if (winCount.first == 3 || winCount.second == 3)
        {
            if (winCount.first == 3 && winCount.second == 3)
            {
                ticket["winning"] = 6;
                numericalPrizeVector[6] += 1;
            }
            else if (winCount.first == 2 || winCount.second == 2)
            {
                ticket["winning"] = 7;
                numericalPrizeVector[7] += 1;
            }
            else if (winCount.first == 1 || winCount.second == 1)
            {
                ticket["winning"] = 8;
                numericalPrizeVector[8] += 1;
            }
            else if (winCount.first == 0 || winCount.second == 0)
            {
                ticket["winning"] = 9;
                numericalPrizeVector[9] += 1;
            }
        }
        else if (winCount.first == 2 || winCount.second == 2)
        {
            if (winCount.first == 2 && winCount.second == 2)
            {
                ticket["winning"] = 10;
                numericalPrizeVector[10] += 1;
            }
            else if (winCount.first == 1 || winCount.second == 1)
            {
                ticket["winning"] = 11;
                numericalPrizeVector[11] += 1;
            }
            else if (winCount.first == 0 || winCount.second == 0)
            {
                ticket["winning"] = 12;
                numericalPrizeVector[12] += 1;
            }
        }
        else
        {
            ticket["winning"] = 0;
        }
    }

    return false;
}
void Sportloto_4_20::recalckPrizeVec(const u64& WinBank)
{
    for (int i = 0; i < 12; i++)
    {
        numericalPrizeVector[i] = WinBank * prizeVector[i] / numericalPrizeVector[i];
    }
}
bool Sportloto_4_20::recalckWin(json& ticket)
{
    ticket["wining"] = numericalPrizeVector[ticket["wining"].get<int>()];
    wins += ticket["wining"].get<int>();
}
std::vector<std::vector<int>> Sportloto_4_20::genWinVec()
{
    std::vector<std::vector<int>> vec;
    vec.push_back(std::vector<int>());
    vec.push_back(std::vector<int>());

    for (int i = 0; i < 4; i++)
    {
        generateNum(20, vec[0]);
        generateNum(20, vec[1]);
    }
    return vec;
}

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

    wins = 0;
    cost = ticket[lotoName]["cost"].get<int>();
    superPrize = ticket[lotoName]["superPrize"].get<int>();
    prizeVector = ticket[lotoName]["prize"].get<std::vector<int>>();
}
std::string Sportloto_5_36::getName()const
{
    return std::string("5_36");
}
bool Sportloto_5_36::genTicket(const int id, nlohmann::json & ticket)const
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
    return ticket["sale"];
}
int Sportloto_5_36::calcWin(const std::vector<std::vector<int>> & ticketVec,const std::vector<std::vector<int>> & winVec)const
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
bool Sportloto_5_36::addWining(json& ticket, const std::vector<std::vector<int>> & winVec)
{
    if (ticket["saled"])
    {
        int winCount = calcWin(ticket["numbers"].get<std::vector<std::vector<int>>>(), winVec);
        if (winCount <= 5)
        {
            ticket["winning"] = prizeVector[winCount];
            wins += prizeVector[winCount];
        }
        else if (winCount == 6)
        {
            ticket["winning"] = superPrize;

            return true;
            //TODO: Переписать суперприз
        }
    }

    return false;
}
std::vector<std::vector<int>> Sportloto_5_36::genWinVec()
{
        std::vector<std::vector<int>> vec;
        vec.push_back(std::vector<int>());
        vec.push_back(std::vector<int>());

        for (int i = 0; i < 5; i++)
        {
            generateNum(36, vec[0]);
        }
        generateNum(4, vec[1]);
        return vec;
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

    wins = 0;
    cost = ticket[lotoName]["cost"].get<int>();
    superPrize = ticket[lotoName]["superPrize"].get<int>();
    prizeVector = ticket[lotoName]["prize"].get<std::vector<int>>();
}
std::string Sportloto_6_45::getName() const
{
    return std::string("6_45");
}
bool Sportloto_6_45::genTicket(const int id, nlohmann::json & ticket)const
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
    return ticket["sale"];
}
int Sportloto_6_45::calcWin(const std::vector<int> & ticketVec,const std::vector<int> & winVec)const
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
bool Sportloto_6_45::addWining(json& ticket,const std::vector<int> & winVec)
{
    if (ticket["saled"])
    {
        int winCount = calcWin(ticket["numbers"].get<std::vector<int>>(), winVec);
        if (winCount <= 5)
        {
            ticket["winning"] = prizeVector[winCount];
            wins += prizeVector[winCount];
        }
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
std::vector<int> Sportloto_6_45::genWinVec()
{
    std::vector<int> vec;

    for (int i = 0; i < 6; i++)
    {
        generateNum(45, vec);
    }
    return vec;
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

    wins = 0;
    cost = ticket[lotoName]["cost"].get<int>();
    superPrize = ticket[lotoName]["superPrize"].get<int>();
    prizeVector = ticket[lotoName]["prize"].get<std::vector<int>>();
}
std::string Sportloto_7_49::getName()const
{
    return std::string("7_49");
}
bool Sportloto_7_49::genTicket(const int id, nlohmann::json & ticket)const
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
    return ticket["sale"];
}
int Sportloto_7_49::calcWin(const std::vector<int> & ticketVec,const std::vector<int> & winVec)const
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
bool Sportloto_7_49::addWining(json& ticket,const std::vector<int> & winVec)
{
    if (ticket["saled"])
    {
        int winCount = calcWin(ticket["numbers"].get<std::vector<int>>(), winVec);
        if (winCount <= 6)
        {
            ticket["winning"] = prizeVector[winCount];
            wins += prizeVector[winCount];
        }
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
std::vector<int> Sportloto_7_49::genWinVec()
{
    std::vector<int> vec;

    for (int i = 0; i < 7; i++)
    {
        generateNum(49, vec);
    }
    return vec;
}
