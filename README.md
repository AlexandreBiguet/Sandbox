# snmpp : Simple Numerical Methods in C++

## Description
There are a lot of numerical methods in C, C++, python, julia, ... 
The goal here is to have fun re-inventing the wheel. 

The mainline is keep it simple to use and to maintain. 

## Notes

The directories `sandbox`, `tests` and `samples` contain little programs to: 
* `sandbox` : try to find a way to implement something I want
* `tests`   : tests if the newly added feature is doing what I want
* `samples` : Show how to use that feature

The directory `src/snmpp/` contains the sources

The `benchmarks` directory contains some benchmark to see if snmpp is not too
 slow: re-inventing the wheel is fun, but there is no fun in inventing a 
 square wheel...  

## Dependencies



* `boost` (version used is 1.64) 


## Contributing

For the moment, the library is quite empty, but its size will increase. 
* Don't hesitate to help me increasing its size
* Don't hesitate to help me increasing its quality


## Building
The `build.py` should do the work: 

``
./build.py --help 
``

## Linking

I am not familiar with the CMake dependency manager. Any help is appreciated :-)

For the moment, there is a **package-config** file which should do the job. 

## How to use snmpp

A good first step should be to see what feature you want to use, and look 
for a corresponding program in the `samples` directory. 

## Documentation

I am not familiar with Doxygen/Sphinx, or any other documentation tool. 
Again, any help is appreciated !  
