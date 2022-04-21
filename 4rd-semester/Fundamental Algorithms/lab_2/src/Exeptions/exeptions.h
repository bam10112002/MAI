#include <exception>

class stdMallocExeption : public std::exception
{
 public:
    stdMallocExeption() : std::exception(){}
    virtual const char* what() const throw() override
    {
        // std::cerr << "Error in standart malloc" << std::endl;
        return "Error in standart malloc";
    }
};
