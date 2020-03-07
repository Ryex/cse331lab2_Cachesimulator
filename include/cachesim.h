/*************************************************************************
 *  filename:  cachesim.h
 *  description:  Implements the cache simulator.
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/
#ifndef CACHESIM_SIM_H
#define CACHESIM_SIM_H

#include <cmath>
#include <random>
#include <iostream> 
#include <climits>

#include "structs.h"
#include "utils.h"

Address_Config build_address_config(Config &config);

Address decompose_address(unsigned int address, Address_Config &aconf);

Cache* build_cache(Address_Config &aconf);

void clean_cache(Cache *cache);

Cache_Sim_Results run_cache_sim(const Trace_Vec *const trace, Cache *cache, Address_Config &aconf, Config &conf);


#endif // !CACHESIM_SIM_H
