#ifndef STOLOTO_H
#define STOLOTO_H
#include "../src/Sourse.h"

class Sportloto;
class Sportloto_4_20;
class Sportloto_5_36;
class Sportloto_6_45;
class Sportloto_7_49;



class GenerateDraw
{
    std::string getDatasetPath();
    json getStatusJson();

public:
    void operator()(const std::string &);
};
class SimulateSale
{
private:
    std::string getDatasetPath();
    json getStatusJson();
    // static void genPackTicketsTh(Sportloto& , std::list<nlohmann::json>&, u32&, std::mutex&, const u64, u32&);
    // static u32 genPackTickets(Sportloto *lot, std::list<nlohmann::json> &l, u32 &currid, const u32 numOfTickets);

public:
    u32 operator()(Sportloto*, const u64, const u64);
};
class FinishLotterey
{
private:
    std::string getDatasetPath();
    json getStatusJson();

    void finish_7_49(Sportloto *lot, const u32 numOfTickets, const u64& fileSize);
    static void Thfinish_7_49(std::string path, Sportloto_7_49* lot, const std::vector<int>& winV);

public:
    void operator()(Sportloto *lot, const u32 numOfTickets, const u64& fileSize);

};

class Lottery
{
private:
    Sportloto *lot;
    u64 drawSize;
    u64 saled;
    u64 fileSize;


    GenerateDraw genDraw;
    SimulateSale sale;
    FinishLotterey finish;

public:
    Lottery(Sportloto*, u64);
    void GenDraw();
    void SimSale();
    void FinishLottery();
};

class Sportloto
{
protected:
    int superPrize;
    int cost;
    u64 wins;

public:
    virtual bool genTicket(const int id, nlohmann::json &ticket) const = 0;
    virtual std::string getName() const = 0;
};

// Спортлото: вспомогательные классы
class Sportloto_4_20 : public Sportloto
{
private:
    std::vector<float> prizeVector;
    std::vector<u64> numericalPrizeVector; // переиспользуется для хранения сумарного банка по каждой категории

    std::pair<int, int> calcWin(const std::vector<std::vector<int>> &ticketVec, const std::vector<std::vector<int>> &winVec);

public:
    Sportloto_4_20();
    std::string getName() const override;
    bool genTicket(const int id, nlohmann::json &ticket) const override;
    bool addWining(json &ticket, const std::vector<std::vector<int>> &winVec);
    void recalckPrizeVec(const u64 &WinBank);
    bool recalckWin(json &ticket);
    virtual std::vector<std::vector<int>> genWinVec();
};
class Sportloto_5_36 : public Sportloto
{
private:
    int calcWin(const std::vector<std::vector<int>> &ticketVec, const std::vector<std::vector<int>> &winVec) const;
    std::vector<int> prizeVector;

public:
    Sportloto_5_36();
    std::string getName() const override;
    bool genTicket(const int id, nlohmann::json &ticket) const override;
    bool addWining(json &ticket, const std::vector<std::vector<int>> &winVec);
    virtual std::vector<std::vector<int>> genWinVec();
};
class Sportloto_6_45 : public Sportloto
{
private:
    int calcWin(const std::vector<int> &ticketVec, const std::vector<int> &winVec) const;
    std::vector<int> prizeVector;

public:
    Sportloto_6_45();
    std::string getName() const override;
    bool genTicket(const int id, nlohmann::json &ticket) const override;
    bool addWining(json &ticket, const std::vector<int> &winVec);
    virtual std::vector<int> genWinVec();
};
class Sportloto_7_49 : public Sportloto
{
private:
    int calcWin(const std::vector<int> &ticketVec, const std::vector<int> &winVec) const;
    std::vector<int> prizeVector;

public:
    Sportloto_7_49();
    std::string getName() const override;
    bool genTicket(const int id, nlohmann::json &ticket) const override;
    bool addWining(json &ticket, const std::vector<int> &winVec);
    std::vector<int> genWinVec();
};

#endif
