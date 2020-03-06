/*************************************************************************
 *  filename:  utils.cc
 *  description:  Utility functions.
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/

#include "utils.h"


std::string& ltrim(std::string& str, const std::string& chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string& rtrim(std::string& str, const std::string& chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string& trim(std::string& str, const std::string& chars)
{
    return ltrim(rtrim(str, chars), chars);
}


unsigned int bit_count(unsigned int n) {
    return (int)std::log2(n)+1;
}

unsigned int count_bits(unsigned int i) {
    int n = 0;
    while (i) {
        n++;
        i= i >> 1;
    }
    return n;
}


