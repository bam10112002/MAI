#include "../src/stoloto/src/Sourse.h"
#include "../src/stoloto/include/Stoloto.h"

bool addWining_7_49_ItemTest(int ind, json & ticket, const std::vector<int> & winVector, int prize);
int addWining_7_49_Test();

bool addWining_6_45_ItemTest(int ind, json & ticket, const std::vector<int> & winVector, int prize);
int addWining_6_45_Test();

bool addWining_5_36_ItemTest(int ind, json & ticket, const std::vector<std::vector<int>> & winVector, int prize);
int addWining_5_36_Test();

bool addWining_4_20_ItemTest(int ind, json & ticket, const std::vector<std::vector<int>> & winVector, float prize);
int addWining_4_20_Test();



int main()
{
    std::cout << "===========>> Testing 7 49 <<============" << std::endl;
    std::cout << addWining_7_49_Test() << " is sucsess" << std::endl << std::endl;

    std::cout << "===========>> Testing 6 45 <<============" << std::endl;
    std::cout << addWining_6_45_Test() << " is sucsess" << std::endl << std::endl;

    std::cout << "===========>> Testing 6 45 <<============" << std::endl;
    std::cout << addWining_5_36_Test() << " is sucsess" << std::endl << std::endl;

    std::cout << "===========>> Testing 4 20 <<============" << std::endl;
    std::cout << addWining_4_20_Test() << " is sucsess" << std::endl << std::endl;
    return 0;
}



bool addWining_7_49_ItemTest(int ind, json & ticket, const std::vector<int> & winVector, int prize)
{
    Sportloto_7_49 lot;
    lot.addWinning(ticket, winVector);

    std::cout << "Test " << ind <<" : " << std::setw(13) << ticket["winning"] << " " << std::setw(13) << prize << "\t";

    if (ticket["winning"] == prize)
    {
        std::cout << "\033[32m SUCSESS \033[0m" << std::endl;
        return true;
    }
    else
    {
        std::cout << "\033[31m Failed \033[0m" << std::endl;
        return false;
    } 
}
int addWining_7_49_Test()
{
    int sucsessCount = 0;
    json ticket;
    std::vector<int> winVec = {1,2,3,4,5,6,8};
    ticket["saled"] = true; 
    ticket["id"] = 1;


    std::vector<int> tickedVec = {1,2,3,4,5,6,7};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_7_49_ItemTest(1, ticket, winVec, 300000);
    
    tickedVec = {1,2,3,4,5,6,8};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_7_49_ItemTest(2, ticket, winVec, 1000000);

    tickedVec = {10,12,13,14,15,16,18};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_7_49_ItemTest(3, ticket, winVec, 0);

    tickedVec = {1,2,13,14,15,16,18};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_7_49_ItemTest(4, ticket, winVec, 100);

    tickedVec = {1,2,3,14,15,16,18};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_7_49_ItemTest(5, ticket, winVec, 200);

    tickedVec = {1,2,3,4,15,16,18};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_7_49_ItemTest(6, ticket, winVec, 700);

    tickedVec = {1,2,3,4,5,16,18};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_7_49_ItemTest(7, ticket, winVec, 6000);

    return sucsessCount;
}

bool addWining_6_45_ItemTest(int ind, json & ticket, const std::vector<int> & winVector, int prize)
{
    Sportloto_6_45 lot;
    lot.addWinning(ticket, winVector);

    std::cout << "Test " << ind <<" : " << std::setw(13) << ticket["winning"] << " " << std::setw(13) << prize << "\t";

    if (ticket["winning"] == prize)
    {
        std::cout << "\033[32m SUCSESS \033[0m" << std::endl;
        return true;
    }
    else
    {
        std::cout << "\033[31m Failed \033[0m" << std::endl;
        return false;
    }
}
int addWining_6_45_Test()
{
    int sucsessCount = 0;
    json ticket;
    std::vector<int> winVec = {1, 2, 3, 4, 5, 6};
    ticket["saled"] = true; 
    ticket["id"] = 1;


    std::vector<int> tickedVec = {1, 2, 3, 4, 5, 6};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_6_45_ItemTest(1, ticket, winVec, 1000000);
    
    tickedVec = {1, 2, 3, 4, 5, 8};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_6_45_ItemTest(2, ticket, winVec, 100000);

    tickedVec = {1, 2, 3, 4, 9, 8};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_6_45_ItemTest(3, ticket, winVec, 1000);

    tickedVec = {1, 2, 3, 14, 9, 8};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_6_45_ItemTest(4, ticket, winVec, 100);

    tickedVec = {1, 2, 13, 14, 9, 8};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_6_45_ItemTest(5, ticket, winVec, 30);

    tickedVec = {1, 12, 13, 14, 9, 8};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_6_45_ItemTest(6, ticket, winVec, 0);

    tickedVec = {11, 12, 13, 14, 9, 8};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_6_45_ItemTest(7, ticket, winVec, 0);

    return sucsessCount;
}

bool addWining_5_36_ItemTest(int ind, json & ticket, const std::vector<std::vector<int>> & winVector, int prize)
{
    Sportloto_5_36 lot;
    lot.addWinning(ticket, winVector);

    std::cout << "Test " << ind <<" : " << std::setw(13) << ticket["winning"] << " " << std::setw(13) << prize << "\t";

    if (ticket["winning"] == prize)
    {
        std::cout << "\033[32m SUCSESS \033[0m" << std::endl;
        return true;
    }
    else
    {
        std::cout << "\033[31m Failed \033[0m" << std::endl;
        return false;
    } 
}
int addWining_5_36_Test()
{
    int sucsessCount = 0;
    json ticket;
    std::vector<std::vector<int>> winVec = {{1, 2, 3, 4, 5}, {1} };
    ticket["saled"] = true; 
    ticket["id"] = 1;


    std::vector<std::vector<int>> tickedVec = {{1, 2, 3, 4, 5}, {1}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_5_36_ItemTest(1, ticket, winVec, 1000000);
    
    tickedVec = {{1, 2, 3, 4, 5}, {2}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_5_36_ItemTest(2, ticket, winVec, 400000);

    tickedVec = {{1, 2, 3, 4, 8}, {1}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_5_36_ItemTest(2, ticket, winVec, 4000);

    tickedVec = {{1, 2, 3, 9, 8}, {1}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_5_36_ItemTest(3, ticket, winVec, 400);

    tickedVec = {{1, 2, 13, 14, 8}, {1}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_5_36_ItemTest(4, ticket, winVec, 40);

    tickedVec = {{1, 12, 13, 14, 8}, {1}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_5_36_ItemTest(5, ticket, winVec, 0);

    tickedVec = {{11, 12, 13, 14, 8}, {1}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_5_36_ItemTest(6, ticket, winVec, 0);
    return sucsessCount;
}

bool addWining_4_20_ItemTest(int ind, json & ticket, const std::vector<std::vector<int>> & winVector, float prize)
{
    Sportloto_4_20 lot;
    lot.addWining(ticket, winVector);

    std::cout << "Test " << std::setw(3) << ind << " :   " << std::setw(4) << ticket["winning"] << " " << std::setw(4) << prize << "\t";

    const double eps = 0.0000001;
    if (fabs(ticket["winning"].get<float>() - prize) < eps)
    {
        std::cout << "\033[32m SUCSESS \033[0m" << std::endl;
        return true;
    }
    else
    {
        std::cout << "\033[31m Failed \033[0m" << std::endl;
        return false;
    } 
}
int addWining_4_20_Test()
{
    int sucsessCount = 0;
    json ticket;
    std::vector<std::vector<int>> winVec = {{1, 2, 3, 4}, {5, 6, 7, 8}};
    ticket["saled"] = true; 
    ticket["id"] = 1;


    std::vector<std::vector<int>> tickedVec = {{1, 2, 3, 4}, {5, 6, 7, 8}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(1, ticket, winVec, 1);
    
    tickedVec = {{1, 2, 3, 4}, {5, 6, 7, 18}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(2, ticket, winVec, 2);

    tickedVec = {{1, 2, 3, 14}, {5, 6, 7, 8}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(3, ticket, winVec, 2);

    tickedVec = {{1, 2, 13, 14}, {5, 6, 7, 8}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(4, ticket, winVec, 3);

    tickedVec = {{1, 2, 3, 4}, {5, 6, 17, 18}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(5, ticket, winVec, 3);

    tickedVec = {{1, 2, 3, 4}, {5, 16, 17, 18}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(6, ticket, winVec, 4);

    tickedVec = {{1, 2, 3, 4}, {15, 16, 17, 18}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(7, ticket, winVec, 5);

    // 3
    tickedVec = {{1, 2, 3, 14}, {5, 6, 7, 18}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(8, ticket, winVec, 6);

    tickedVec = {{1, 2, 3, 14}, {51, 6, 7, 8}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(9, ticket, winVec, 6);

    tickedVec = {{1, 2, 13, 14}, {5, 16, 7, 8}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(10, ticket, winVec, 7);

    tickedVec = {{1, 2, 3, 14}, {5, 6, 17, 18}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(11, ticket, winVec, 7);

    tickedVec = {{1, 2, 3, 14}, {5, 16, 17, 18}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(12, ticket, winVec, 8);

    tickedVec = {{1, 2, 3, 14}, {15, 16, 17, 18}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(13, ticket, winVec, 9);



    // 2
    tickedVec = {{1, 2, 13, 14}, {15, 16, 7, 8}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(14, ticket, winVec, 10);

    tickedVec = {{1, 2, 13, 14}, {15, 16, 17, 8}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(15, ticket, winVec, 11);

    tickedVec = {{1, 2, 13, 14}, {15, 16, 17, 18}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(16, ticket, winVec, 12);

    tickedVec = {{1, 12, 13, 14}, {15, 16, 17, 18}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(17, ticket, winVec, 0);


    tickedVec = {{1, 12, 13, 14}, {15, 16, 17, 8}};
    ticket["numbers"] = tickedVec;
    sucsessCount += addWining_4_20_ItemTest(18, ticket, winVec, 0);

    return sucsessCount;
}