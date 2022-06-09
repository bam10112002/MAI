#include <cmath>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using u8 = unsigned char;

class Hamming
{
private:
    std::vector<u8> hammingArray;
    unsigned int hammingSize;
    unsigned int massiveSize;

    int GetAdditionalBits(int massiveSize);
    int get(int ind) const;
    bool inverse(int ind);

public:
    Hamming(int massiveSize);
    Hamming(const Hamming& forCopy);
    bool operator==(const Hamming& right);
    friend std::istream& operator >> (std::istream& in, Hamming& hm);
    friend std::ostream& operator << (std::ostream &os, const Hamming &hm);
    
    void setArr(const std::vector<u8>& array);
    std::vector<u8> getArr();
    std::vector<u8> getHemmingArr();
    void binaryPrint() const;
    int ChangeError();

    bool set(int ind, int val); // TODO: in private
    void CalckHemmingBits();
};