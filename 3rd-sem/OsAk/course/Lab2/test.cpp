#include <string>
#include <iostream>

int main(int argc, char)
{

    std::string a = "-245.2";
    std::cout << std::stod(a) + 1;

    return 0;
}