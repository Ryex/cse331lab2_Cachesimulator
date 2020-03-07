/*************************************************************************
 *  filename:  load.cc
 *  description:  Read conf and trace files
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/

#include "load.h"

Access_Type to_actype(char c) {
    switch (c) {
        case 'l':
            return LOAD;
        case 's':
             return STORE;
    }      
    throw actype_conversion_err();
}

const int ADDRESS_SIZE = 32;

Config read_conf(std::string &conf_filename) {
    Config conf;
    
    std::ifstream conf_file(conf_filename);

    std::cout << "Using conf from file [" << conf_filename << "]" << std::endl;

    if(!conf_file) {
        std::cerr << "Config file [" << conf_filename <<"] can not be opened!" << std::endl;
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(2);
    }

    std::vector<int> lines;
    int l = 1;
    while (!conf_file.eof()) {
        int i;
        std::string str;
        getline(conf_file, str);
        str = trim(str);
        if (str.empty()) {
            break;
        }
        try {
            i = std::stoi(str);
        } catch (std::invalid_argument const &e) {
            std::cerr << "Bad input in conf file line " << l << ": Not a valid integer." << std::endl;
            exit(2);
        } catch (std::out_of_range const &e) {
            std::cerr << "Bad input in conf file line " << l << ": integer out of range." << std::endl;
            exit(2);
        }
        lines.push_back(i);

        l++;
    }

    if (lines.size() < 6) {
        std::cerr << "Config file [" << conf_filename << "] invalid! missing [" << (6 - lines.size()) << "] lines." << std::endl;
        exit(2);
    } else if (lines.size() > 6) {
        std::cerr << "Config file [" << conf_filename << "] invalid! [" << (lines.size() - 6) << "] extra lines." << std::endl;
        exit(2);
    }

    
    if (!power_2_non_neg(lines[0])) {
        std::cerr << "Config file [" << conf_filename << "] invalid! line 1, line_size: must be a positive power of 2." << std::endl;
        exit(2);
    }
    conf.line_size = lines[0];

    
    if (!power_2_non_neg(lines[1])) {
        std::cerr << "Config file [" << conf_filename << "] invalid! line 2, associativity: must be a positive power of 2." << std::endl;
        exit(2);
    }
    conf.associativity = lines[1];
    
    if (!power_2_non_neg(lines[2])) {
        std::cerr << "Config file [" << conf_filename << "] invalid! line 3, data_size: must be a positive power of 2." << std::endl;
        exit(2);
    }
    conf.data_size = lines[2];

    try {
        conf.replacement = to_policy<Replace_Policy>(lines[3]);
    } catch (policy_conversion_err const &e) {
        std::cerr << "Config file [" << conf_filename << "] invalid! line 4, replacement policy: must be 0 or 1." << std::endl;
        exit(2); 
    }

    conf.miss_penalty = lines[4];

    try {
        conf.allocate = to_policy<Alloc_Policy>(lines[5]);
    } catch (policy_conversion_err const &e) {
        std::cerr << "Config file [" << conf_filename << "] invalid! line 6, allocate policy: must be 0 or 1." << std::endl;
        exit(2); 
    }

    conf.address_size = ADDRESS_SIZE;

    return conf;
}

Trace_Line read_trace_line(std::string &line) {
    Trace_Line trace_line;
    
    std::stringstream line_s(line);

    int pos = line_s.tellg();
    char c;
    line_s >> c;
    if (line_s.fail()) {
        throw trace_line_exception("failed to read load/store charater", pos);
    }
    try {
        trace_line.access_type = to_actype(c);
    } catch (actype_conversion_err const &e) {
        std::string msg = "Bad load/store charater [";
        msg = msg + c + "]";
        throw trace_line_exception(msg.c_str(), pos);
    }

    pos = line_s.tellg();

    line_s >> std::hex >> trace_line.address;

    if (line_s.fail()) {
        throw trace_line_exception("failed to read hex address", pos);
    }

    pos = line_s.tellg();

    line_s >> trace_line.islma;

    if (line_s.fail()) {
        throw trace_line_exception("failed to read instruction count", pos);
    }

    return trace_line;
}

Trace_Vec* read_trace(std::string &trace_filename) {
    Trace_Vec *trace = new Trace_Vec();

    std::ifstream trace_file(trace_filename);

    std::cout << "Reading trace from file [" << trace_filename << "]" << std::endl;

    if(!trace_file) {
        std::cerr << "Config file [" << trace_filename <<"] can not be opened!" << std::endl;
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(2);
    }

    int l = 1;
    while (!trace_file.eof()) {
        std::string str;
        getline(trace_file, str);
        str = trim(str);
        if (str.empty()) {
            continue;
        }
        Trace_Line trace_line;
        
        try {
           trace_line = read_trace_line(str);
        } catch (trace_line_exception const &e) {
            std::cerr << "Bad input in trace file line " << l << ": " << e.what() << std::endl;
            exit(2);
        }
        
        trace->push_back(trace_line);

        l++;
    }

    return trace;
}
