/*************************************************************************
 *  filename:  cachesim.cc
 *  description:  Implements the cache simulator.
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/

#include <cmath>
#include <random>
#include <iostream> 
#include <climits>

#include "cachesim.h"

#ifdef DEBUG_VERBOSE
const bool VERBOSE = true;
#else
const bool VERBOSE = false;
#endif // DEBUG

Address_Config build_address_config(Config &config)
{
    Address_Config aconf;

    aconf.cache_bits = bit_count(config.data_size << 10);
    aconf.line_bits = bit_count(config.line_size);
    aconf.num_blocks = 1 << (aconf.cache_bits - aconf.line_bits);
    if (config.associativity > 1)
    {
        aconf.lines_per_set = config.associativity;
        aconf.set_bits = bit_count(aconf.num_blocks / aconf.lines_per_set);
    }
    else
    {
        aconf.lines_per_set = 1;
        aconf.set_bits = aconf.cache_bits - aconf.line_bits;
    }
    aconf.num_sets = 1 << aconf.set_bits;
    aconf.tag_bits = config.address_size - aconf.line_bits - aconf.set_bits;

    return aconf;
}

Address decompose_address(unsigned int address, Address_Config &aconf)
{

    Address addr;
    addr.tag = address >> (aconf.line_bits + aconf.set_bits);
    addr.set_index = (address << aconf.tag_bits) >> (aconf.tag_bits + aconf.line_bits);
    addr.block_offset = address << (aconf.tag_bits + aconf.set_bits);

    return addr;
}

Cache *build_cache(Address_Config &aconf)
{
    Cache *cache = new Cache();

    cache->sets = new Cache_Set_Vec(aconf.num_sets);

    for (unsigned int i = 0; i < aconf.num_sets; i++)
    {
        cache->sets->at(i).blocks = new Cache_Block_Vec(aconf.lines_per_set);
        cache->sets->at(i).oldest_access = 0;
    }

    return cache;
}

void clean_cache(Cache *cache)
{
    for (unsigned int i = 0; i < cache->sets->size(); i++)
    {
        delete cache->sets->at(i).blocks;
    }

    delete cache->sets;
}

Cache_Sim_Results run_cache_sim(const Trace_Vec *const trace, Cache *cache, Address_Config &aconf, Config &conf)
{

    Cache_Sim_Results results;

    results.loads = 0;
    results.stores = 0;
    results.hits = 0;
    results.misses = 0;
    results.load_hits = 0;
    results.load_misses = 0;
    results.store_hits = 0;
    results.store_misses = 0;
    results.evictions = 0;
    results.write_backs = 0;
    results.run_cycles = 0;
    results.memory_cycles = 0;
    results.memory_instructions = 0;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, aconf.lines_per_set - 1);

    int empty = -1;
    bool hit = false;
    int access = 0;

    for (unsigned int i = 0; i < trace->size(); i++)
    {
        const Trace_Line tl = trace->at(i);

        if (VERBOSE)
        {
            std::cout << i << ": " << trace->at(i) << std::endl;
        }

        Address addr = decompose_address(tl.address, aconf);

        Cache_Set &set = cache->sets->at(addr.set_index);

        set.oldest_access = UINT_MAX;
        switch (tl.access_type) {
            case Access_Type::LOAD:
                results.loads += 1;
                break;
            case Access_Type::STORE:
                results.stores += 1;
                break;
        }

        for (unsigned int j = 0; j < aconf.lines_per_set; j++)
        {
            if (set.blocks->at(j).valid == true)
            {
                if (set.blocks->at(j).tag == addr.tag)
                {
                    results.hits += 1;
                    set.blocks->at(j).last_access = access;
                    access++;

                    hit = true;

                    switch (tl.access_type) {
                    case Access_Type::LOAD:
                        results.load_hits += 1;
                        break;
                    case Access_Type::STORE:
                        results.store_hits += 1;
                        if (conf.allocate == Alloc_Policy::WRITE)
                        {
                            set.blocks->at(j).dirty = true;
                        }
                        break;
                    default:
                        break;
                    }
                }
                else if (set.blocks->at(j).last_access < set.oldest_access)
                {
                    set.oldest_access = set.blocks->at(j).last_access;
                    set.oldest = j;
                }
            }
            else if (empty == -1)
            {
                empty = j;
            }
        }

        if (!hit)
        {
            results.misses += 1;

            if (VERBOSE)
            {
                std::cout << "MISS: " << tl.access_type << std::endl;
            }

            bool load = false;
            switch (tl.access_type)
            {
            case Access_Type::LOAD:
                results.load_misses += 1;
                load = true;
                break;
            case Access_Type::STORE:
                results.store_misses += 1;
                if (conf.allocate == Alloc_Policy::WRITE)
                {
                    load = true;
                }
                else
                {
                    load = false;
                }
                break;
            default:
                load = true;
                break;
            }
            if (load)
            {
                if (empty > -1)
                {
                    set.blocks->at(empty).tag = addr.tag;
                    set.blocks->at(empty).valid = 1;
                    set.blocks->at(empty).last_access = access;
                    set.blocks->at(empty).dirty = false;
                    access++;
                }
                else if (empty < 0)
                {
                    results.evictions += 1;
                    int replace;
                    switch (conf.replacement)
                    {
                    case Replace_Policy::RANDOM:
                        replace = distribution(generator);
                        break;
                    case Replace_Policy::FIFO:
                        replace = set.oldest;
                        break;
                    default: // should never happend but default to FIFO
                        replace = set.oldest;
                        if (VERBOSE)
                        {
                            std::cout << "BAD Rreplacment policy" << std::endl;
                        }
                        break;
                    }
                    if (conf.allocate == Alloc_Policy::WRITE && set.blocks->at(replace).dirty)
                    {
                        results.write_backs += 1;
                    }
                    set.blocks->at(replace).tag = addr.tag;
                    set.blocks->at(replace).valid = 1;
                    set.blocks->at(replace).last_access = access;
                    set.blocks->at(replace).dirty = false;
                    access++;
                }
            }

            results.run_cycles += tl.islma + conf.miss_penalty; // add penelty cyecles
            results.memory_cycles += conf.miss_penalty;
        }
        else
        {
            if (VERBOSE)
            {
                std::cout << "HIT: " << tl.access_type << std::endl;
            }

            results.run_cycles += tl.islma + 1; // 1 cycle for hit
            results.memory_cycles += 1;

            empty = -1;
            hit = false;
        }
        results.memory_instructions += 1;
    }

    results.hit_rate = (double)results.hits / (double)(results.hits + results.misses);
    results.load_hit_rate = (double)results.load_hits / (double)(results.load_hits + results.load_misses);
    results.store_hit_rate = (double)results.store_hits / (double)(results.store_hits + results.store_misses);

    results.avg_access = (double)results.memory_cycles / (double)results.memory_instructions;

    return results;
}
