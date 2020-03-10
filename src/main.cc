/*************************************************************************
 *  filename:  cachesim.cc
 *  description:  main driver file.
 *  authors:  Powers, Rachel
 *  class:CSE 331
 *  instructor:  Zheng
 *  assignment:  Lab #2
 *  assigned:  2/20/2020/due:3/5/2020
 ************************************************************************/

#include "main.h"

void print_usage() {
    const char *usage = "Usage: ./cache-sim conf_file trace_file\n";
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

    Address_Config aconf = build_address_config(conf);


    std::cout << aconf;
    
    Trace_Vec* trace = read_trace(trace_file);

    Cache* cache = build_cache(aconf);

    Cache_Sim_Results results = run_cache_sim(trace, cache, aconf, conf);

    std::cout << results;

    clean_cache(cache);
    delete cache;
    delete trace;

    write_out_file(trace_file, results);

    return 0;

}

void write_out_file(std::string filename, Cache_Sim_Results &results) {
    std::string outfilename = fs::path(filename).filename().string() + ".out";


    std::cout << "writing output to [" << outfilename << "]" << std::endl;
    std::ofstream out_file(outfilename);

    out_file << results.hit_rate << std::endl;
    out_file << results.load_hit_rate << std::endl;
    out_file << results.store_hit_rate << std::endl;
    out_file << results.run_cycles << std::endl;
    out_file << results.avg_access << std::endl;

    out_file.close();
}
