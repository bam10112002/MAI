#include "../src/finishLottery.h"
#include "../src/genDraw.h"
#include "../src/simulateSale.h"

class Stoloto
{
 private:

 public:

}


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
