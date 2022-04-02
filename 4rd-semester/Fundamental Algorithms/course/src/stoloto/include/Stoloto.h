#ifndef STOLOTO_H
#define STOLOTO_H
#include "../src/Sourse.h"

class Sportloto
{
 protected:
   int superPrize;
   int cost;

 public:
    virtual void genTicket(const int id, nlohmann::json & ticket) = 0;

};

class GenerateDraw
{
   std::string getDatasetPath();
   json getStatusJson();
 public:
    std::string operator()(const std::string & );

};

class SimulateSale
{
 private:
   std::string getDatasetPath();
   json getStatusJson();
   static void genPackTicketsTh(Sportloto & lot, std::list<nlohmann::json> & l, u32 & currid,
                          std::mutex & mtx, const u32 numOfTickets);
   static void genPackTickets(Sportloto* lot, std::list<nlohmann::json> & l, u32 & currid, const u32 numOfTickets);

 public:
    void operator()(const std::string &, const u32);
};

class FinishLotterey
{
 private:

 public:
   void operator()(const std::string &);

};

class Lottery
{
 private:

 public:
   GenerateDraw genDraw;
   SimulateSale sale;
   FinishLotterey finish;
};


// Спортлото: вспомогательные классы
class Sportloto_4_20  : public Sportloto
{
 private:
   std::vector<float> prizeVector;
   std::vector<u64>  numericalPrizeVector; // переиспользуется для хранения сумарного банка по каждой категории

   std::pair<int,int> calcWin(const std::vector<std::vector<int>> & ticketVec,const std::vector<std::vector<int>> & winVec);
   // void recalcWin(json& ticket);
   void recalcVec();
 
 public:

   Sportloto_4_20();
   void genTicket(const int id, nlohmann::json & ticket) override;
   bool addWining(json& ticket, const std::vector<std::vector<int>> & winVec);
};
class Sportloto_5_36  : public Sportloto
{
 private:
   int calcWin(const std::vector<std::vector<int>> & ticketVec,const std::vector<std::vector<int>> & winVec);
   std::vector<int> prizeVector;

 public:
   Sportloto_5_36();
   void genTicket(const int id, nlohmann::json & ticket) override;
   bool addWinning(json& ticket, const std::vector<std::vector<int>> & winVec);

};
class Sportloto_6_45  : public Sportloto
{
 private:
   int calcWin(const std::vector<int> & ticketVec,const std::vector<int> & winVec);
   std::vector<int> prizeVector;

 public:
   Sportloto_6_45();
   void genTicket(const int id, nlohmann::json & ticket) override;
   bool addWinning(json& ticket,const std::vector<int> & winVec);
};
class Sportloto_7_49  : public Sportloto
{
private:
   int calcWin(const std::vector<int> & ticketVec,const std::vector<int> & winVec);
   std::vector<int> prizeVector;

 public:
   Sportloto_7_49();
   void genTicket(const int id, nlohmann::json & ticket) override;
   bool addWinning(json & ticket,const std::vector<int> & winVec);
   
};

#endif
