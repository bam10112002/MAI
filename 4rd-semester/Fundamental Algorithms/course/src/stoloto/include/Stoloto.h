#ifndef STOLOTO_H
#define STOLOTO_H
#include "../src/Sourse.h"
#include "../src/log.h"
// #include "../src/find.h"
// #include <QNetworkReply>

class Sportloto;
class Sportloto_4_20;
class Sportloto_5_36;
class Sportloto_6_45;
class Sportloto_7_49;



class GenerateDraw
{
    std::string getDatasetPath();
    json getStatusJson();
    void createLog(const std::string &);
public:
    void operator()(const std::string &);
};
class SimulateSale
{
private:
    std::string getDatasetPath();
    json getStatusJson();
    void writeLog(const u32& saled, const u32& drawSize,const std::string& path) const;
public:
    u32 operator()(Sportloto*, const u64, const u64);
};
class FinishLotterey
{
private:
    std::string getDatasetPath();
    json getStatusJson();

    u32 finish_7_49(Sportloto *lot, const u32 quantityOfTickets, const u64& fileSize);
    static void Thfinish_7_49(std::string path, Sportloto_7_49* lot, 
                const std::vector<int>& winV, std::mutex & mtx, u32&);

    u32 finish_6_45(Sportloto *lot, const u32 quantityOfTickets, const u64& fileSize);
    static void Thfinish_6_45(std::string path, Sportloto_6_45* lot, 
                const std::vector<int>& winV, std::mutex & mtx, u32&);

    u32 finish_5_36(Sportloto *lot, const u32 quantityOfTickets, const u64& fileSize);
    static void Thfinish_5_36(std::string path, Sportloto_5_36* lot,
             const std::vector<std::vector<int>>& winV, std::mutex & mtx, u32&);

    u32 finish_4_20(Sportloto *lot, const u32 quantityOfTickets, const u64& fileSize);
    static void Thfinish_4_20(std::string path, Sportloto_4_20* lot, 
            const std::vector<std::vector<int>>& winV, std::mutex & mtx, u32&);
    static void Thfinish_rec_4_20(std::string path, Sportloto_4_20* lot, 
            std::mutex & mtx, u32&);

public:
    void operator()(Sportloto *lot, const u32 quantityOfTickets,
                    const u64& fileSize, const u64& income);

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
    virtual ~Sportloto(){}
    virtual bool genTicket(const int id, nlohmann::json &ticket) const = 0;
    virtual std::string getName() const = 0;
    virtual size_t Cost() const = 0;
};

// Спортлото: вспомогательные классы
class Sportloto_4_20 : public Sportloto
{
private:
    std::vector<float> prizeVector;
    std::vector<u64> numericalPrizeVector; // переиспользуется для хранения сумарного банка по каждой категории

    std::pair<int, int> calcWin(const std::vector<std::vector<int>> &ticketVec, 
                                const std::vector<std::vector<int>> &winVec);

public:
    Sportloto_4_20();
    std::string getName() const override;
    size_t Cost() const override;
    bool genTicket(const int id, nlohmann::json &ticket) const override;
    bool addWining(json &ticket, const std::vector<std::vector<int>> &winVec);
    void recalckPrizeVec(const u64 &WinBank);
    bool recalckWin(json &ticket);
    virtual std::vector<std::vector<int>> genWinVec();
};
class Sportloto_5_36 : public Sportloto
{
private:
    int calcWin(const std::vector<std::vector<int>> &ticketVec, 
                const std::vector<std::vector<int>> &winVec) const;
    std::vector<int> prizeVector;

public:
    Sportloto_5_36();
    std::string getName() const override;
    size_t Cost() const override;
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
    size_t Cost() const override;
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
    size_t Cost() const override;
    bool genTicket(const int id, nlohmann::json &ticket) const override;
    bool addWining(json &ticket, const std::vector<int> &winVec);
    std::vector<int> genWinVec();
};

#endif
