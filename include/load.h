/*************************************************************************
 *  filename:  load.h
 *  description:  Read conf and trace files, header
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/
#ifndef CACHESIM_LOAD_H
#define CACHESIM_LOAD_H

#include <exception>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>



#include "structs.h"

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

class actype_conversion_err: public std::exception {
    virtual const char* what() const throw() {
        return "char not 'l' or 's'";
    }
};

Access_Type to_actype(char c);

class trace_line_exception : public std::runtime_error {
	int pos;
    
    public:
    	trace_line_exception(const char* msg, int pos_ ) : std::runtime_error(msg),
        	pos (pos_)
        {
        }
        int get_pos() const { return pos; }
       
};

Config read_conf(std::string &conf_filename);
Trace_Line read_trace_line(std::string &line);
Trace_Vec* read_trace(std::string &trace_filename);

#endif // !CACHESIM_LOAD_H
