# Atech Interview Problem

This repository contains the solution to the problem proposed for the Jr Position at Atech. 

Furthermore, a detailed explanation of the solution can be found in this repo's wiki.

## Problem Overview 

Given an M by N matrix comprised only of ones and zeros, find the rectangle with largest area containing only 1 and return the value of its area.

For example: 
```c
{
    {1, 0, 1, 0, 0},
    {1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0},
};

```
For the matrix above the program must return `6`.

## Running Locally 

The repository contains the unit testing framework "Unity" as a git submodule, therefore it is necessary to clone recursively:

```bash
$ git clone --recurse-submodules https://github.com/Pedro4064/atech_interview.git
```

Afterwards, you can change into the cloned directory and do the initial build:
```bash
$ cd atech_interview && mkdir build && cd build && cmake .. && cd ..
```

And from this point on you can re-compile and run all the tests from the root of the repo by doing:
```bash
$ cmake --build build --target test_run && ./build/test_run
```
All teste cases are located inside the [tests directory.](./tests/test_max_area.c)

## Solution Explanation

As previously state, a detailed solution for the problem can be found on this repo's wiki.