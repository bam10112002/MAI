#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <list>
#include <fstream>
#include <ctime>
#include "../../json/single_include/nlohmann/json.hpp"

#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>

using u32 = uint32_t;
using json = nlohmann::json;

class stoloto
{
 public:
    virtual void genTicket(const int id, nlohmann::json & ticket) = 0;
};

class stoloto_4_20  : public stoloto
{
 public:
    stoloto_4_20();
    void genTicket(const int id, nlohmann::json & ticket) override;
    virtual void calcWin(json& ticket, std::vector<std::vector<int>> winVec);
};

class stoloto_5_36  : public stoloto
{
 public:
    stoloto_5_36();
    void genTicket(const int id, nlohmann::json & ticket) override;
    virtual void calcWin(json& ticket, std::vector<std::vector<int>> winVec);
};

class stoloto_6_45  : public stoloto
{
 public:
    stoloto_6_45();
    void genTicket(const int id, nlohmann::json & ticket) override;
    virtual void calcWin(json& ticket, std::vector<int> winVec);
};

class stoloto_7_49  : public stoloto
{
 public:
    stoloto_7_49();
    void genTicket(const int id, nlohmann::json & ticket) override;
    virtual void calcWin(json& ticket, std::vector<int> winVec);
};

void simulateSale(std::string path, const u32 numOfTickets);
