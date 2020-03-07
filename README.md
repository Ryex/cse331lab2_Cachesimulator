## To Build

run
```shell
$ make clean 
$ make release
```

## To Run

```
$ ./build/cache-sim
Usage: ./cache-sim conf_file trace_file
$ ./build/cache-sim ./conf/2way-nwa.conf ./traces/gcc.trace
Using conf from file [./confs/2way-nwa.conf]
Config {
    address_size: 32 bits
    line_size: 32 bytes
    associativity: 2
    data_size: 128KB
    replacment: FIFO
    miss_penalty: 70 cycles
    allocate: NO_WRITE
}
Address_Config {
    cache_bits: 17
    set_bits: 11
    num_blocks: 4096
    num_sets: 2048
    line_bits: 5
    lines_per_set: 2
    tag_bits: 16
}
Reading trace from file [./traces/gcc.trace]
...

```
