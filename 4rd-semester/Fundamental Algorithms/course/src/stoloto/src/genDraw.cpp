// #include "genDraw.h"
#include "../include/Stoloto.h"

void GenerateDraw::operator()(const std::string & loteryName)
{
    std::string path = ""; 
    json status = getStatusJson();

    if (status[loteryName.c_str()]["status"].get<std::string>() == std::string("ended"))
    {
        int draw = status[loteryName.c_str()]["draw"].get<int>() + 1;
        path = getDatasetPath() + loteryName + "/" + std::to_string(draw);
        int dir = mkdir(path.c_str(), 0777);
        if (dir != 0)
        {
            perror("mkdir::");
            std::cout << "path = " << path << std::endl;
            exit(-1);
        }

        status[loteryName.c_str()]["draw"] = draw;
        // status[loteryName.c_str()]["status"] = "started"; //TODO: вернуть
        std::ofstream of("conf/status.json");
        of << status;
    }
    else    
    {
        //TODO: throw LotteryError;  
        std::cout << "\n\033[31mERROR: draw sale is not ended please wait\033[0m\n" << std::endl;
        exit(-1);
    }
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