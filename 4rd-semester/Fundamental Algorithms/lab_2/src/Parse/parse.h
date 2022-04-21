#include <fstream>
#include <iostram>
#include <map>
#include <string>

class Parser
{
private:
    map<std::string, void*> var;

public:
    Parser(const std::string & fName);
    void parseLine(const std::string & line);

}