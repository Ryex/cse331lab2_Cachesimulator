/*************************************************************************
 *  filename:  main.h
 *  description:  main driver function
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/
#ifndef CACHESIM_MAIN_H
#define CACHESIM_MAIN_H

#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "structs.h"
#include "utils.h"
#include "load.h"
#include "cachesim.h"

void print_usage();

void write_out_file(std::string filename, Cache_Sim_Results &results);


#endif // !CACHESIM_MAIN_H
