#include "simulateSale.h"
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());


// Sourse
void generateNum(const int border, std::vector<int> & vec)
{
    bool flag = true;
    while (flag)
    {
        flag = false;
        int gen = (rng() % border) + 1;
        for (const int num : vec)
        {
            if (num == gen)
                flag = true;
        }

        if (!flag)
            vec.push_back(gen);
    }
}

void genPackTicketsTh(stoloto & lot, std::list<nlohmann::json> & l, u32 & currid,
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

void genPackTickets(stoloto* lot, std::list<nlohmann::json> & l, u32 & currid, const u32 numOfTickets)
{
    std::mutex mtx;
    std::list<nlohmann::json> l1, l2, l3, l4, l5;
    // int saled1 = , saled2 = 0, saled3 = 0, saled4 = 0, saled5 = 0; 

    std::thread th1(genPackTicketsTh, std::ref(*lot), std::ref(l1),
                    std::ref(currid), std::ref(mtx), numOfTickets/5);
    std::thread th2(genPackTicketsTh, std::ref(*lot), std::ref(l2),
                    std::ref(currid), std::ref(mtx), numOfTickets/5);
    std::thread th3(genPackTicketsTh, std::ref(*lot), std::ref(l3),
                    std::ref(currid), std::ref(mtx), numOfTickets/5);
    std::thread th4(genPackTicketsTh, std::ref(*lot), std::ref(l4),
                    std::ref(currid), std::ref(mtx), numOfTickets/5);
    std::thread th5(genPackTicketsTh, std::ref(*lot), std::ref(l5),
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

void simulateSale(std::string path, const u32 numOfTickets)
{
    stoloto* lot = new stoloto_7_49();
    u32 currid = 0;
    // u32 saled = 0;
    std::list<nlohmann::json> list;
    nlohmann::json tickets = {};
    const u32 FSize = 500000;

    for (u32 i = 0; i < numOfTickets / FSize; i++)
    {
        // Эмуляция продажи билетов
        currid = i * FSize;
        genPackTickets(lot, list, currid, FSize);
        tickets["mainVector"] = list;

        //Запись в файл
        std::string p2 = path + "/" +   std::to_string(i*FSize) + "-" + std::to_string((i+1)*FSize) + ".json";
        std::cout << p2 << std::endl;
        std::ofstream of(p2);
        of << tickets;

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
stoloto_4_20::stoloto_4_20()
{
    srand(time(0));
}
void stoloto_4_20::genTicket(const int id, nlohmann::json & ticket)
{   
    ticket = {};
    ticket["id"] = id;
    if ((rng() % 20) == 1)
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
void calcWin(json& ticket, std::vector<std::vector<int>> winVec)
{

}

stoloto_5_36::stoloto_5_36()
{
    srand(time(0));
}
void stoloto_5_36::genTicket(const int id, nlohmann::json & ticket)
{
    ticket = {};
    ticket["id"] = id;
    if ((rng() % 20) == 1)
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
void calcWin(json& ticket, std::vector<std::vector<int>> winVec)
{
    std::vector<std::vector<int>> ticketVec = ticket["numbers"].get<std::vector<std::vector<int>>>();
    int count = 0;
    for(int i = 0; i < 5; i++)
    {
        if (find(ticketVec[0].begin(), ticketVec[0].end(), winVec[i]) != ticketVec[0].end())
            count++;
    }
    
    if (find(ticketVec[1][0] == ticketVec[0][0])
    {
        //TODO: superprize
    }
    else
    {
        ticket["winning"] = 4 * pow(10,count);
    }
}

stoloto_6_45::stoloto_6_45()
{
    srand(time(0));
}
void stoloto_6_45::genTicket(const int id, nlohmann::json & ticket)
{
    ticket = {};
    ticket["id"] = id;
    if ((rng() % 20) == 1)
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
void calcWin(json& ticket, std::vector<std::vector<int>> winVec)
{

}

stoloto_7_49::stoloto_7_49()
{
    srand(time(0));
}
void stoloto_7_49::genTicket(const int id, nlohmann::json & ticket)
{
    ticket = {};
    ticket["id"] = id;
    if ((rng() % 20) == 1)
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
void calcWin(json& ticket, std::vector<std::vector<int>> winVec)
{

}
