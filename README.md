# C++ Containers Library
> A c++ Library that fully reimplements a few containers and components of the c++ standard library

## Table of Contents
* [Overview](#overview)
* [Features](#features)
* [Setup](#setup)
* [Usage](#usage)
* [Project Status](#project-status)
* [Acknowledgements](#acknowledgements)

## Overview
- This library reimplements these containers: vector, stack and map and some c++ metaprogramming functionalities such as enable_if and is_integral.
- The containers replicate the exact same behavior as the STL ones with very similar performance (they respect the time complexity of each container's method as stated by the c++ standard)
- They were implemented using c++98 and therefore only the c++98 behavior of the above containers was replicated.
- In the same way the STL code lives in the std namespace, All of this library's code lives in the ft namespace to avoid any naming collisions.

## Features
- For each container, there is a test program meant to check the correctness of this implementation compared to the STL version. The makefile compiles each program and runs a testing script that tests ft::containers against std::containers to check if their behavior is similar and also benchmarks both programs for performance testing (more on the testing part in the usage section)
- Awesome feature 2
- Awesome feature 3

## Setup
What are the project requirements/dependencies? Where are they listed? A requirements.txt or a Pipfile.lock file perhaps? Where is it located?

Proceed to describe how to install / setup one's local environment / get started with the project.


## Usage
How does one go about using it?
Provide various use cases and code examples here.

`write-your-code-here`


## Project Status
Project is: _complete_


## Acknowledgements
This project is part of my 1337 school (42 network) curriculum. So I would like to thank my school for giving me the opportunity to work on a project that taught me a lot of new things.
