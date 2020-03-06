/*************************************************************************
 *  filename:  utils.h
 *  description:  Utility function forward declarations.
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/
#ifndef CACHESIM_UTILS_H
#define CACHESIM_UTILS_H 

#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
 
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
 
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

inline bool power_2_non_neg(int i) {
    return i > 0 && (i & (i - 1)) == 0;
}

template< typename T >
std::string int_to_hex( T i )
{
  std::stringstream stream;
  stream << "0x" 
         << std::setfill ('0') << std::setw(sizeof(T)*2) 
         << std::hex << i;
  return stream.str();
}

unsigned int bit_count(unsigned int n);
unsigned int count_bits(unsigned int n);

#endif // !CACHESIM_UTILS_H
