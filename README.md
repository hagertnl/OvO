# OvO (OpenMP Validation for Offload)

```
  ___
 (o,o)
<  .  >
--"-"---
```

[![Build Status](https://travis-ci.org/TApplencourt/OvO.svg?branch=master)](https://travis-ci.org/TApplencourt/OvO)

This repository containt OpenMP offloading tests for most of the C++ Math Function (`cmath` and `complex`). For example see https://github.com/TApplencourt/OvO/tree/master/tests/math_cpp11 for the c++11 functions.

It also containt a large set of tests for Hierarchical parralellism. For example, see https://github.com/TApplencourt/OvO/tree/master/tests/hp_reduction for the reductions testing.

The test can be run using `ovo.sh run` with the CXX / CXXFLAGS you like to enable OpenMP offloading.

```
$ CXX="clang++" CXXFLAGS="-fopenmp -std=c++17" MAKEFLAGS='-j32 --output-sync=target' ./ovo.sh run tests/math_cpp11 tests/math_cpp17
Running tests/math_cpp11 | Saving log in results/2020-04-06_17-01_travis-job-24888c4a-3841-4347-8ccd-6f1e8d034e30/math_cpp11
clang++ -std=c++17 isgreater_bool_float_float.cpp -o isgreater_bool_float_float.exe
clang++ -std=c++17 isgreater_bool_double_double.cpp -o isgreater_bool_double_double.exe
clang++ -std=c++17 truncf_float_float.cpp -o truncf_float_float.exe
[...]
```
Result can be see wit `ovo.sh display`.

```
$ ./ovo.sh display
>> results/2020-04-06_17-01_travis-job-24888c4a-3841-4347-8ccd-6f1e8d034e30/math_cpp11
307 / 307 ( 100% ) pass [ 0 compilation failures / 0 runtime failures ]
```

## How to run

```
$ ./ovo.sh -g
Usage:
  ovo.sh gen [--v5]
  ovo.sh run [<test_folder>...] [--avoid_long_double]
  ovo.sh display [--failure | --pass] [--avoid_long_double] [<result_folder>...]
  ovo.sh clean
(base) [tapplencourt@jlselogin2 OmpVal]$ ./ovo.sh -h
Omphval.sh a OpenMP test generator.
Usage:
  ovo.sh gen [--v5]
  ovo.sh run [<test_folder>...] [--avoid_long_double]
  ovo.sh display [--failure | --pass] [--avoid_long_double] [<result_folder>...]
  ovo.sh clean

  Options:
   gen                 Generate the ./tests directory containting all the tests
     v5                  Generate openmp v5 tests (loop construct for example)

   run                 Will run all the test specifier by <test_folder>.
                       The log are stored in the ./results/${uuid}_$(hostname)/<test_folder>/ directory
                       More information are saved in '{compilation,runtime}.log' files of those result folder
                       Use tradional Flags to control the execusion (CXX, CXXFLAGS, MAKEFLAGS, OMP, OMP_TARGET_OFFLOAD, etc)
     <test_folder>       Folder containing the tests to run (default: ./tests/ )

   display             Display the Error message of failling tests.
     <result_folder>     Folder to display (default: ./results/ )
     avoid_long_double   Don't print long_double tests. If used in conjunction with working, will not print the working long double if they exit

Example:
  - hierarchical parallelism tests
       OMP_TARGET_OFFLOAD=mandatory CXX='icc' CXXFLAGS='-qnextgen -fiopenmp -fopenmp-targets=spir64=-fno-exceptions' MAKEFLAGS='-j8 --output-sync=target' ./ovo.sh run ./tests/hp_*
  - Display a sumarry of result the result.
      ./ovol.sh diplay --avoid_long_double  results/*/math_cpp11
```

# How to read logs files.

When running with `run`, two log files will be create for each`test_folder`.
 
Only the code who didn't compile or run are printed when using `./run.sh display`.
The error code repported are the one given by `make`. A quick tranlasion table is:

    - `Aborted` : Wrong value
    - `Killed` : Hanging, killed by `killall -9`
    - `Segmentation  fault` : ???
    - `Error 1 (ignored)` : Something else

For more information see the log file and check for the error.

# Where are the tests?!

Check `tests` folder. They can be re-generated by `gen`.
They are generated using the `.jinja2` templates located at `src/template/`.
If you don't like one test, just remove it. 

# Requirement
 - bash >3.2 (bash 3.2 was realeased in 2006-10-12!)
 - python 3
 - make
 - jinja2 (optional. Only needed to regenered the tests)
