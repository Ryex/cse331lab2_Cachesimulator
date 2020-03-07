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
    case Replace_Policy::RANDOM:
        os << "RANDOM";
        break;
    case Replace_Policy::FIFO:
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
    case Alloc_Policy::NO_WRITE:
        os << "NO_WRITE";
        break;
    case Alloc_Policy::WRITE:
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
       << "    address_size: " << conf.address_size << " bits" << std::endl
       << "    line_size: " << conf.line_size << " bytes" << std::endl
       << "    associativity: " << conf.associativity << std::endl
       << "    data_size: " << conf.data_size << "KB" << std::endl
       << "    replacment: " << conf.replacement << std::endl
       << "    miss_penalty: " << conf.miss_penalty << " cycles" << std::endl
       << "    allocate: " << conf.allocate << std::endl
       << "}" << std::endl;
    return os;
}

enum Access_Type { LOAD, STORE };

inline std::ostream& operator<<(std::ostream& os, const Access_Type& p ) {
    switch (p)
    {
    case Access_Type::LOAD:
        os << "LOAD";
        break;
    case Access_Type::STORE:
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
    os << "Trace_Line { " << tl.access_type << " " << int_to_hex(tl.address) << " " << tl.islma << " }";
    return os;
}

typedef std::vector<Trace_Line> Trace_Vec;

struct Address {
    unsigned int tag;
    int set_index;
    int block_offset;
};

struct Cache_Block {
    bool valid;
    bool dirty;
    unsigned int tag;
    unsigned int last_access;
};

typedef std::vector<Cache_Block> Cache_Block_Vec;

struct Cache_Set {
    Cache_Block_Vec *blocks;
    unsigned int oldest_access;
    unsigned int oldest;
};

typedef std::vector<Cache_Set> Cache_Set_Vec;

struct Cache {
    Cache_Set_Vec *sets;
};

struct Address_Config {
    unsigned int cache_bits;
    unsigned int set_bits;
    unsigned int num_blocks;
    unsigned int num_sets;
    unsigned int line_bits;
    unsigned int lines_per_set;
    unsigned int tag_bits;
};

inline std::ostream& operator<<(std::ostream& os, const Address_Config& conf) {
    os << "Address_Config {" << std::endl
       << "    cache_bits: " << conf.cache_bits << std::endl
       << "    set_bits: " << conf.set_bits << std::endl
       << "    num_blocks: " << conf.num_blocks << std::endl
       << "    num_sets: " << conf.num_sets << std::endl
       << "    line_bits: " << conf.line_bits << std::endl
       << "    lines_per_set: " << conf.lines_per_set << std::endl
       << "    tag_bits: " << conf.tag_bits  << std::endl
       << "}" << std::endl;
    return os;
}


struct Cache_Sim_Results {
    int hits;
    int misses;
    double hit_rate;
    int load_hits;
    int load_misses;
    double load_hit_rate;
    int store_hits;
    int store_misses;
    double store_hit_rate;
    int evictions;
    int write_backs;
    int run_cycles;
    int memory_cycles;
    int memory_instructions;
    double avg_access;
};

inline std::ostream& operator<<(std::ostream& os, const Cache_Sim_Results& results) {
    os << "Cache_Sim_Results {" << std::endl
       << "    hits: " << results.hits << std::endl
       << "    misses: " << results.misses << std::endl
       << "    hit_rate: " << results.hit_rate << std::endl
       << "    load_hits: " << results.load_hits << std::endl
       << "    load_misses: " << results.load_misses << std::endl
       << "    load_hit_rate: " << results.load_hit_rate  << std::endl
       << "    store_hits: " << results.store_hits << std::endl
       << "    store_misses: " << results.store_misses << std::endl
       << "    store_hit_rate: " << results.store_hit_rate  << std::endl
       << "    evictions: " << results.evictions << std::endl
       << "    write_backs: " << results.write_backs << std::endl
       << "    run_cycles: " << results.run_cycles << std::endl
       << "    memory_cycles: " << results.memory_cycles << std::endl
       << "    memory_instructions: " << results.memory_instructions << std::endl
       << "    avg_access: " << results.avg_access  << std::endl
       << "}" << std::endl;
    return os;
}

#endif // !CACHESIM_STRUCTS_H
