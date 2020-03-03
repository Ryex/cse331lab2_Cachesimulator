## To Build

run
```shell
$ make clean 
$ make
```

## To Run

```
$ ./cachesim
Usage: ./cachesim conf_file trace_file
$ ./cachesim ./conf/2way-nwa.conf ./traces/gcc.trace
Using conf from file [./confs/2way-nwa.conf]
Config {
    line_size: 32
    associativity: 2
    data_size: 128
    replacment: FIFO
    miss_penalty: 70
    allocate: NO_WRITE
}
Reading trace from file [./traces/gcc.trace]
...
```
