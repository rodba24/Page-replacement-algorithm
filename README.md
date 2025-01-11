# Page Replacement Algorithms Simulator

This project is a submission for Operating Systems course, focusing on simulating and comparing three common page replacement algorithms: **Optimal**, **FIFO (First-In-First-Out)**, and **LRU (Least Recently Used)**. The program calculates the number of page faults for each algorithm using predefined page-reference strings and a fixed number of memory frames.

## Project Objective

The goal of this project is to:
- Demonstrate understanding of memory management concepts in operating systems.
- Implement and compare different page replacement algorithms.
- Analyze the trade-offs between algorithms in terms of efficiency and performance.

## Features

- Simulates three algorithms:
  - **Optimal**: Predicts future page usage to minimize page faults.
  - **FIFO**: Replaces the oldest page in memory.
  - **LRU**: Tracks and replaces the least recently used page.
- Compares the algorithms using predefined page-reference strings.
- Provides clear output showing the number of page faults for each algorithm.

## Code Overview

### Main Functions

1. **`optimal(int pages[])`**  
   Simulates the Optimal page replacement algorithm by analyzing future page references.
   
2. **`fifo(int pages[])`**  
   Simulates the FIFO page replacement algorithm using a circular queue.

3. **`lru(int pages[])`**  
   Simulates the LRU page replacement algorithm by tracking the last usage of pages.

### Input

The program uses predefined page-reference strings such as:

```c
int page1[] = {2, 6, 9, 2, 4, 8, 1, 7, 3, 0, 8, 2, 1, 2, 9, 5, 7, 2, 8, 5};
