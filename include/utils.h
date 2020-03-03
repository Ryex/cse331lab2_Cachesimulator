#ifndef cachsim_utils_h
#define cachsim_utils_h 

#include <string>

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
 
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
 
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

template< typename T >
std::string int_to_hex( T i )
{
  std::stringstream stream;
  stream << "0x" 
         << std::setfill ('0') << std::setw(sizeof(T)*2) 
         << std::hex << i;
  return stream.str();
}

#endif
