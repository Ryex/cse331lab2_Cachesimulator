/*************************************************************************
 *  filename:  cachesim.cc
 *  description:  Implements the cache simulator.
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/

#include "cachesim.h"

void print_usage() {
    const char *usage = "Usage: ./cachesim conf_file trace_file\n";
    std::cout << usage;
}

int main (int argc, char *argv[]) {

    std::vector<std::string> args;
    std::string current_exec_name = argv[0]; // Name of the current exec program

    if (argc > 1) {
        args.assign(argv + 1, argv + argc);
    }

    if (args.size() != 2) {
        print_usage();
        exit(1);
    }

    std::string conf_file = args[0];
    std::string trace_file = args[1];

    Config conf = read_conf(conf_file);

    std::cout << conf;

    Trace_Vec* trace = read_trace(trace_file);


    for (int i = 0; i < 20; i++) {
        std::cout << i << ": " << trace->at(i);
    }

    delete trace;
    return 0;

}
