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

Address_Config build_address_config(Config &config) {
    Address_Config aconf;

    aconf.cache_bits = bit_count(config.data_size);
    aconf.line_bits = bit_count(config.line_size);
    aconf.set_bits = aconf.cache_bits - aconf.line_bits;
    aconf.num_blocks = std::pow(2, aconf.set_bits);
    if (config.associativity > 1) {
        aconf.set_bits = bit_count(aconf.num_blocks / config.associativity);
        aconf.num_blocks = std::pow(2, aconf.set_bits);
    }
    aconf.num_blocks = std::pow(2, aconf.set_bits);
    aconf.tag_bits = config.address_size - aconf.line_bits - aconf.set_bits;

    return aconf;
}

Address decompose_address(unsigned int address, Address_Config &aconf) {

    Address addr;
    addr.tag = address >> (aconf.line_bits + aconf.set_bits);
    addr.set_index = (address << aconf.tag_bits) >> (aconf.tag_bits + aconf.line_bits);
    addr.block_offset = address << (aconf.tag_bits + aconf.set_bits);

    return addr;

}
