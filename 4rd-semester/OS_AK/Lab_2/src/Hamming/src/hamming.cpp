#include "../include/hamming.h"

Hamming::Hamming(int _massiveSize)
{
    hammingArray = std::vector<u8>(static_cast<int>(std::ceil(GetAdditionalBits(_massiveSize)/8.0)));
    massiveSize = _massiveSize;
    hammingSize = GetAdditionalBits(massiveSize);
}
Hamming::Hamming(const Hamming& forCopy)
{
    massiveSize = forCopy.massiveSize;
    hammingSize = GetAdditionalBits(massiveSize);
    hammingArray = forCopy.hammingArray;
    // hammingArray = new u8[static_cast<int>(std::ceil(GetAdditionalBits(massiveSize)/8.0))];
    // for (int i = 0; i < static_cast<int>(std::ceil(GetAdditionalBits(massiveSize)/8.0)); i++)
    // {
    //     hammingArray[i] = forCopy.hammingArray[i];
    // }
}
bool Hamming::operator==(const Hamming& right)
{
    for (int i = 1; i < hammingSize; i *= 2)
    {
        if (this->get(i-1) != right.get(i-1))
        {
            return false;
        }
    }
    return true;
}
std::ostream& operator << (std::ostream &os, const Hamming &hm)
{
    for (auto& obj :hm.hammingArray)
    {
        os.write((char*)&obj, sizeof(obj));
    }
    return os;
}
std::istream& operator >> (std::istream& in, Hamming& hm)
{
    for (int i = 0; i < static_cast<int>(std::ceil(hm.hammingSize/8.0)); i++)
    {
        in.read((char*)&(hm.hammingArray[i]), sizeof(hm.hammingArray[i]));
    }
    return in;
}

int Hamming::GetAdditionalBits(int massiveSize)
{
    int n = std::log2(massiveSize);
    return massiveSize + n + 1;
}
void Hamming::binaryPrint()const 
{
    // std::cout << "hammingSize = "<< hammingSize << std::endl; 
    for (int i = 0; i < hammingSize; i++)
    {
        if (i%8 == 0 && i != 0)
            std::cout << ": ";
        std::cout << get(i) << " ";
    }
    std::cout << std::endl;
}
void Hamming::setArr(const std::vector<u8>& array)
{
    int degree_2 = 1, old_pos = 0;
    for (int i = 0; i < hammingSize; i++)
    {
        if (i + 1 == degree_2)
        {
            set(i,0);
            degree_2 *= 2;
        }
        else
        {
            int charInd = old_pos/(sizeof(u8)*8);
            set(i, (array[charInd] & (128 >> old_pos % (sizeof(u8)*8))));
            old_pos++;
        }
    }
    CalckHemmingBits();
}
std::vector<u8> Hamming::getArr()
{
    int degree_2 = 1, old_pos = 0;
    u8 ch = 0;
    std::vector<u8> vec;
    for (int i = 0; i < hammingSize; i++)
    {
        if (i + 1 == degree_2)
        {
            degree_2 *= 2;
        }
        else
        {
            if (get(i))
                ch |=  (128 >> old_pos);
               
            old_pos++;
            if (old_pos == 8)
            {
                vec.push_back(ch);
                ch = 0;
                old_pos=0;
            }
            
        }
    }
    // std::cout << std::endl;
    return vec;
}
std::vector<u8> Hamming::getHemmingArr()
{
    return hammingArray;
}
void Hamming::CalckHemmingBits()
{
    for (int i = 1; i < hammingSize; i *= 2)
    {
        set(i-1,0);
    }

    // this->binaryPrint();
    int degree_2 = 1, old_pos = 0;
    for (int i = 0; i < hammingSize; i++)
    {
        if (i + 1 == degree_2)
        {
            // std::cout << "degree: " << degree_2 << "| ";
            int ind = degree_2-1;
            int sum = 0;
            while (ind < hammingSize)
            {
                for (int j = 0; j < degree_2; j++)
                {
                    if (ind >= hammingSize)
                        break;
                    
                    // std::cout << get(ind) << " ";
                    sum += get(ind);
                    sum = sum % 2;
                    ind++;
                }
                ind = ind + degree_2;
            }
            set(i, sum);
            // std::cout << std::endl;
            degree_2 *= 2;
        }
    }
}
int Hamming::ChangeError()
{
    Hamming oldHm(*this);
    this->CalckHemmingBits();
    int sum = 0;
    for (int i = 1; i < hammingSize; i *= 2)
    {
        if (this->get(i-1) != oldHm.get(i-1))
        {
            sum += i;
        }
    }
    this->inverse(sum-1);
    this->CalckHemmingBits();
    return sum-1;
}

int Hamming::get(int ind) const
{
    /*
        return -1: ошибка индекс невалиден
        return число: значение бита в int формете 
    */
    
    if (ind < 0 || ind > hammingSize)
        return -1;
    int charInd = ind/(sizeof(u8)*8);
    if (hammingArray[charInd] & (128 >> ind % (sizeof(u8)*8)))
        return 1;
    return 0;
}
bool Hamming::set(int ind, int val)
{
    /* 
        return false: индекс невалиден
        return true: установка прошла успешно 
    */

    if (ind < 0 || ind > hammingSize)
        return false;

    int charInd = ind/(sizeof(u8)*8);
    if (val)
        hammingArray[charInd] |=  (128 >> ind % (sizeof(u8)*8));
    else 
        hammingArray[charInd] &= ~(128 >> ind % (sizeof(u8)*8));
    return true;
}
bool Hamming::inverse(int ind)
{
     /* 
        return false: индекс невалиден
        return true: установка прошла успешно 
    */

    if (ind < 0 || ind > hammingSize)
    {
        return false;
    }
    else
    {
        int charInd = ind/(sizeof(u8)*8);
        hammingArray[charInd] ^= (128 >> ind % (sizeof(u8)*8));
    }

    return true;
}
