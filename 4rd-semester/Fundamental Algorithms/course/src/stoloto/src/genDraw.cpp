#include "genDraw.h"


std::string gendraw(const std::string sportloto)
{
    std::ifstream fd("conf/status.json");
    json status = {};
    fd >> status;

    if (status[sportloto.c_str()]["status"].get<std::string>() == std::string("ended"))
    {
        int draw = status[sportloto.c_str()]["draw"].get<int>() + 1;
        std::string path = "datasets/" + sportloto + "/" + std::to_string(draw);
        mkdir(path.c_str(), 0777);

        status[sportloto.c_str()]["draw"] = draw;
        status[sportloto.c_str()]["status"] = std::string("start");
        std::ofstream of("conf/status.json");
        of << status;
        return path;
    }
    else    
    {
        std::cout << "error draw sale is not ended please wait" << std::endl;
        exit(-1);
    }
}
