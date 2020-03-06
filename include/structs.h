/*************************************************************************
 *  filename:  structs.h
 *  description:  config and trace structs used to store data
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/
#ifndef CACHESIM_STRUCTS_H
#define CACHESIM_STRUCTS_H

#include <string>
#include <vector>

#include "utils.h"

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
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}

struct Config {
    int address_size;
    int line_size;
    int associativity;
    int data_size;
    Replace_Policy replacement;
    int miss_penalty;
    Alloc_Policy allocate;
};

inline std::ostream& operator<<(std::ostream& os, const Config& conf) {
    os << "Config {" << std::endl
       << "    address_size: " << conf.address_size << std::endl
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

typedef std::vector<Trace_Line> Trace_Vec;

struct Address {
    int tag;
    int set_index;
    int block_offset;
};

struct Line {
    int valid;
    unsigned int tag;
};

struct Set {
    std::vector<Line> lines;
};

struct Cache {
    std::vector<Set> sets;
};

struct Address_Config {
    unsigned int line_bits;
    unsigned int cache_bits;
    unsigned int num_blocks;
    unsigned int set_bits;
    unsigned int tag_bits;
};

inline std::ostream& operator<<(std::ostream& os, const Address_Config& conf) {
    os << "Address_Config {" << std::endl
       << "    line_bits: " << conf.line_bits << std::endl
       << "    cache_bits: " << conf.cache_bits << std::endl
       << "    num_blocks: " << conf.num_blocks << std::endl
       << "    set_bits: " << conf.set_bits << std::endl
       << "    tag_bits: " << conf.tag_bits  << std::endl
       << "}" << std::endl;
    return os;
}

#endif // !CACHESIM_STRUCTS_H
