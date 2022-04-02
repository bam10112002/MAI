#include "../include/Stoloto.h"
#include "./Sourse.h"

// void finishLottery(const std::string sportloto)
// {
//     const u32 FSize = 500000;
//     std::ifstream fd("conf/status.json");
//     json status = {};
//     fd >> status;
//     if (status[sportloto.c_str()]["status"].get<std::string>() == std::string("start"))
//     {
//         std::string path = "datasets/" + sportloto + "/" + std::to_string(status[sportloto.c_str()]["draw"].get<int>());
//         json file;
//         u32 saled = 0;
        // for (u32 i = 0; i < numOfTickets / FSize; i++)
        // {
        //     std::string p2 = path + "/" +   std::to_string(i*FSize) + "-" + std::to_string((i+1)*FSize) + ".json";
        //     fd.open(p2);
        //     fd >> file;
        //     for (json::iterator it = file["mainVector"].begin(); it != file["mainVector"].end(); ++it) {
        //         if((*it)["sale"])
        //             ++saled; 
        //     } 
        // }
//         status[sportloto.c_str()]["status"] = std::string("ended");
//         std::ofstream of("conf/status.json");
//         of << status;
//     }
//     else    
//     {
//         std::cout << "error draw sale is not started please generate draw" << std::endl;
//         exit(-1);
//     }
// }