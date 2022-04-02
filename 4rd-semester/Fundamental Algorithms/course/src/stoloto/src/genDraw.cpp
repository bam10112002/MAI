// #include "genDraw.h"
#include "../include/Stoloto.h"

std::string GenerateDraw::operator()(const std::string & sportloto)
{
    std::string path = "";
    json status = getStatusJson();

    if (status[sportloto.c_str()]["status"].get<std::string>() == std::string("ended"))
    {
        int draw = status[sportloto.c_str()]["draw"].get<int>() + 1;
        path = getDatasetPath() + sportloto + "/" + std::to_string(draw);
        int dir = mkdir(path.c_str(), 0777);
        if (dir != 0)
        {
            perror("mkdir::");
            std::cout << "path = " << path << std::endl;
            exit(-1);
        }

        status[sportloto.c_str()]["draw"] = draw;
        status[sportloto.c_str()]["status"] = std::string("start");
        std::ofstream of("conf/status.json");
        of << status;
    }
    else    
    {
        //TODO: trow LotteryError;  
        std::cout << "error draw sale is not ended please wait" << std::endl;
        exit(-1);
    }
    return path;
}

std::string GenerateDraw::getDatasetPath()
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

json GenerateDraw::getStatusJson()
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