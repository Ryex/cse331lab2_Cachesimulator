/*************************************************************************
 *  filename:  cachesim.h
 *  description:  Stuct and forward declarations.
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/
#ifndef cachesim_h
#define cachesim_h

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "../include/utils.h"

enum Replace_Policy {
    RANDOM = 0,
    FIFO = 1
};

inline std::ostream& operator<<(std::ostream& os, const Replace_Policy& p ) {
    switch (p)
    {
    case RANDOM:
        os << "RANDOM";
        break;
    case FIFO:
        os << "FIFO";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}

enum Alloc_Policy {
    NO_WRITE = 0,
    WRITE = 1
};

inline std::ostream& operator<<(std::ostream& os, const Alloc_Policy& p) {
    switch (p)
    {
    case NO_WRITE:
        os << "NO_WRITE";
        break;
    case WRITE:
        os << "WRITE";
    default:
        os << "Unknown";
        break;
    }
    return os;
}

class policy_conversion_err: public std::exception {
    virtual const char* what() const throw() {
        return "int not 0 or 1";
    }
};

template<typename T>
T to_policy(int i) {
    switch (i) {
        case 0 :
        case 1 :
            return static_cast<T>(i);
    }
    throw policy_conversion_err();
}

struct Config {
    int line_size;
    int associativity;
    int data_size;
    Replace_Policy replacement;
    int miss_penalty;
    Alloc_Policy allocate;
};

inline std::ostream& operator<<(std::ostream& os, const Config& conf) {
    os << "Config {" << std::endl
       << "    line_size: " << conf.line_size << std::endl
       << "    associativity: " << conf.associativity << std::endl
       << "    data_size: " << conf.data_size << std::endl
       << "    replacment: " << conf.replacement  << std::endl
       << "    miss_penalty: " << conf.miss_penalty << std::endl
       << "    allocate: " << conf.allocate << std::endl
       << "}" << std::endl;
    return os;
}

enum Access_Type { LOAD, STORE };

inline std::ostream& operator<<(std::ostream& os, const Access_Type& p ) {
    switch (p)
    {
    case LOAD:
        os << "LOAD";
        break;
    case STORE:
        os << "STORE";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}

class actype_conversion_err: public std::exception {
    virtual const char* what() const throw() {
        return "char not 'l' or 's'";
    }
};

Access_Type to_actype(char c) {
    switch (c) {
        case 'l':
            return LOAD;
        case 's':
             return STORE;
    }      
    throw actype_conversion_err();
}

struct Trace_Line {
    Access_Type access_type;
    unsigned int address;
    int islma;
};

inline std::ostream& operator<<(std::ostream& os, const Trace_Line& tl) {
    os << "Trace_Line {" << std::endl
       << "    access_type: " << tl.access_type << std::endl
       << "    address: " << int_to_hex(tl.address) << std::endl
       << "    inst_since_lma: " << tl.islma << std::endl
       << "}" << std::endl;
    return os;
}


class trace_line_exception : public std::runtime_error {
	int pos;
    
    public:
    	trace_line_exception(const char* msg, int pos_ ) : std::runtime_error(msg),
        	pos (pos_)
        {
        }
        int get_pos() const { return pos; }
       
};

typedef std::vector<Trace_Line> Trace_Vec;

void print_usage();
Config read_conf(std::string &conf_filename);
Trace_Line read_trace_line(std::string &line);
Trace_Vec* read_trace(std::string &trace_filename);

#endif
