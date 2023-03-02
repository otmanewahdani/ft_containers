# C++ Containers Library
> A c++ Library that fully reimplements a few containers and components of the c++ standard library.

## Table of Contents
* [Overview](#overview)
* [Features](#features)
* [Setup](#setup)
* [Usage](#usage)
  * [Demo programs](#compiling-and-running-the-demo-programs)
  * [Testing](#running-the-tests)
  * [Using it in your code](#using-the-library-in-your-own-program)
* [Project Status](#project-status)
* [Acknowledgements](#acknowledgements)

## Overview
- This library reimplements these containers: vector, stack and map (and their corresponding iterators) and some c++ metaprogramming functionalities such as enable_if and is_integral.
- The containers replicate the exact same behavior as the STL ones with very similar performance (they respect the time complexity of each container's method as stated by the c++ standard).
- They were implemented using c++98 and therefore only the c++98 behavior of the above containers was replicated.
- In the same way the STL code lives in the std namespace, All of this library's code lives in the ft namespace to avoid any naming collisions.

## Features
- The AVL binary search tree is the underlying associative data structure used in the map container class.
- the AVL was itself implemented as an independent templated container class so it is highly reusable in any other code.
- For each container, there is a test program meant to check the correctness of this implementation compared to the STL version. The makefile compiles each program and runs a testing script that tests ft::containers against std::containers to check if their behavior is similar and also benchmarks both programs for performance testing (more on the testing part in the usage section).

## Setup
- It is a no brainer that if you want to use this code you will need a c++ compiler (preferrably gcc or clang).
- A Unix environment was used to develop and test this library, specifically Linux and Darwin for MacOs. So no guarantees that it will compile smoothly in any other environment. For Linux, Bash is needed. And for a Darwin-based Macos, Zsh works best with the building process.


## Usage
First in your terminal, clone and go to the base directory:
```bash
git clone https://github.com/otmanewahdani/ft_containers.git && cd ft_containers
```
- ### Compiling and running the demo programs
  The Makefile has rules for compiling 3 separate demo programs (which are the main.cpp's in each container's directory) that demonstrate the 3 containers: vector, stack and map. So for compiling and running the demo program, do the following :
  
  ```bash
  make map && cd map && ./map
  ```
  :bulb: The same procedure works for the other two containers, just substitute map with vector or stack.<br />
  
  :warning: The program output is long and unintelligible since it's only meant to be used by the testing script.<br />
  
- ### Running the tests
  Like it was explained in the features section, each container can be benchmarked and tested separately against the original STL containers. Thus make sure you are in the base directory (same location as the Makefile) and run the following to execute the tests:
  ```bash
    make test-map
  ```
  :bulb: if you want to test the other containers, just keep the same command and substitute map with the name of the container.<br />
  #### Illustration
  <img src="./.img/container testing illustration.gif" alt="Illustration of how container tests are run" width="600" height="100" />
- ### Using the Library in your own program
  1. #### Including the library's header files
      First, in your preprocessor include directive use only the name of the header file like this:
      ```c++
      #include <vector.hpp>
      #include <map.hpp>
      #include <stack.hpp>
      #include <type_traits.hpp>
      #include <utility.hpp>
      #include <iterator.hpp>
      #include <algorithm.hpp>
      ```
      :bulb: It's not necessary to include all of the header files, just include the ones you need.<br />
      
      Then, specify the path to ft_containers in any way you want (I included an example on how you might wanna do it, just replace parent-directories with the file path leading to ft_containers) and supplement the following flags to your compiler:
      ```bash
      export FT_CONTAINERS_PATH="parent-directories/ft_containers"
      export FT_CONTAINERS_INCS="-I$FT_CONTAINERS_PATH/vector/incs -I$FT_CONTAINERS_PATH/map/incs -I$FT_CONTAINERS_PATH/stack/incs -I$FT_CONTAINERS_PATH/algorithm -I$FT_CONTAINERS_PATH/iterator -I$FT_CONTAINERS_PATH/utility -I$FT_CONTAINERS_PATH/type_traits"
      
      <your-compiler> <your-program-source-files> $FT_CONTAINERS_INCS
      ```
      :bulb: Again you don't need to use all the flags. Only use what you need<br />
  2. #### Using the containers in your code
      They will be used the same way as the STL containers with only a slight difference. Since the standard containers are defined in the std namespace, std is prepended along with the scope resolution operator to the name of the container like this:
      ```c++
      std::vector<int> emptyVector;
      ```
      But for this library ft needs to be prepended to all type names like the following:
      ```c++
      ft::map<int, char*> emptyMap;
      ```

## Project Status
Project is: _complete_


## Acknowledgements
This project is part of my 1337 school (42 network) curriculum. So I would like to thank my school for giving me the opportunity to work on a project that taught me a lot of new things.
