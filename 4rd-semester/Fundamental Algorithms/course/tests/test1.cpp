#include <iostream>
#include <vector>
#include <string>
#include "../src/json/single_include/nlohmann/json.hpp"


typedef struct my
{
public:
    std::string str;
    std::vector<int> vec;
}My;

int main(int argc, char const *argv[])
{
    nlohmann::json j = {};
    std::vector<int> vec = {1,2,3,4,5};

    j["name"] =  "artem";
    j["vector"] = vec;

    My obg;
    obg = j;

    
    return 0;
}
