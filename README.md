# Sandbox

This repo contains a lot test programs. There are 'language-directories' in
which I just test some stuff (which is dependent on the language)

I plan to add some sandbox projects too in order to try some stuff more deeply.
These projects will have to do with python asyncio, tensorflow / pytorch

## Language dependent test
* **C** (legacy): a lot of tests I performed during my phd thesis. Most of the
time, the tests don't have a proper compile chain, sometimes a Makefile can be
found. What I can say is that you have to use gcc to compile (not clang)
because I I used the GCC local function definition. Standard must be C99.
  - Some Gnu Scientific Library tests
  - Some numerical Recipes tests
  - Some backtrace utilies
  - A contour level plot utility (that was before I knew matplotlib...)
* **CMake** :
  - a cmake-format tool
  - how package generation works
  - how to build for / using Xcode IDE
* **C++** : The C++ directory contains a some test programs all gathered in a
unique CMake project
  - Boost
    - any
    - asio
    - concept
    - geometry
    - graph
    - optional
    - Plugins (using boost dll)
  - GeographicLib
  - Standard Library (some tests)
* **LaTex** (legacy) : I don't even remember what it is I was testing when I
  wrote all those files. This had something to do with my Phd thesis.
* **Python** :
  - Generators
  - List comprehension
  - asyncio

## Small Projects
- **snmpp** : stands for simple numerical methods in cpp. I started it a few
  month ago as a unique git repo, but it is more a project for fun than
  anything else. 
