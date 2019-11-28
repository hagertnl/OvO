# OmpVal

## How to run

```
run.sh a OpenMP test generator
Usage:
 ./run.sh -h | --help
 ./run.sh [ -g | --gen ] [ -r | --run] [ -d | --display ]

   -h --help          Show this screen.
   -g, --gen          Generate the tests
   -r, --run          Complile and run the tests
   -d, --display      Display the summary of the test

 Example:
CXX="icx" CXXFLAGS="-fiopenmp -fopenmp-targets=spir64=-fno-exceptions"  ./run.sh -g -r -d
 ```

# How to read logs fils.

When running with `-r`, two log files will be create in each directory of the `omp_test` (e.g. `omp_tests/atomic/sound/*.log`).
They correspond to the output of make for compiling (`exe.log`) and running (`run.log`).
 
Only the code who didn't compile or run are printed when using `./run.sh -d` (see `result/icx.txt` for one example).
The error code repported are the one given by `make`. A quick tranlasion table is:
    -  `Aborted` : Wrong value
    - `Killed` : Hanging, killed by `killall -9`
    - 'Segmentation  fault' : ???
    - ` Error 1 (ignored) : Something else

For more information see the log file and check for the error.

# Requirement
 - python 3.
 - jinja2
