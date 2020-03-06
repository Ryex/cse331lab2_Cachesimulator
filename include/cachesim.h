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

#include "structs.h"
#include "utils.h"

Cache* build_cache(Config &config);

Address_Config build_address_config(Config &config);

Address decompose_address(unsigned int address, Config &config );



#endif // !CACHESIM_SIM_H
