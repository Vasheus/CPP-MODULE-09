# *This project has been created as part of the 42 curriculum.*

# C++ Modules (09)

## Description

This repository contains a series of C++ exercises from the 42 curriculum.  
This module focuses on the Standard Template Library (STL), algorithmic problem-solving, and efficient data processing.

The goal is to learn how to manipulate real-world datasets using containers, implement parsing systems, and understand the performance differences between data structures and sorting algorithms.

---

## Topics Covered

- STL containers (vector, deque, stack, etc.)  
- Iterators and container operations  
- Parsing and file handling  
- Algorithm complexity analysis  
- Stack-based evaluation  
- Sorting algorithms (merge-insert / Ford–Johnson)  
- Performance measurement (timing execution)  

---

## Project Structure

Each exercise is independent:

ex00/
ex01/
ex02/


---

## Concepts Overview

### Exercise 00 – Bitcoin Exchange

This exercise focuses on file parsing, data validation, and lookup operations using a historical database.

You must build a program that evaluates the value of Bitcoin on a given date.

### Exercise 01 – Reverse Polish Notation (RPN)

This exercise implements a stack-based mathematical expression evaluator.

Core concept:
Evaluating expressions using **Last-In-First-Out (LIFO)** structure.

#### Exercice 03


##  Deep Dive – Ford–Johnson / Merge-Insertion Sort

This algorithm is not a standard merge sort. It is designed to **minimize the number of comparisons**, not just time complexity.

###  Core Idea

Instead of directly sorting everything, the algorithm works in phases:

#### 1. Pairing Phase
Split elements into pairs: (3, 5), (9, 7), (4, 2), ...

Each pair is ordered internally: (min, max)


We separate:
- **Main chain (larger elements)**
- **Pending elements (smaller elements)**

---

#### 2. Main Chain Sorting
Sort only the **max elements** first:

This creates a partially sorted backbone: 5, 7, 9, ...

This step reduces future comparisons significantly.

---

#### 3. Jacobsthal Insertion Strategy


The key optimization is how we insert remaining elements.

Instead of inserting in order, we follow the **Jacobsthal sequence**:

J(n) = J(n-1) + 2 × J(n-2)

Sequence: 0, 1, 1, 3, 5, 11, 21, ...


This determines the **optimal insertion order**.

Why?
Because inserting elements in this order minimizes:
- binary search depth
- total comparisons
- worst-case insertion cost

---

#### 4. Binary Insertion Phase

Each pending element is inserted into the sorted chain using: binary search → O(log n)


So overall structure becomes:
- O(n log n) complexity
- but with fewer comparisons than standard merge sort

---

## 📊 Complexity Insight

| Algorithm         | Comparisons | Complexity |
|------------------|------------|------------|
| Merge Sort       | ~n log n   | O(n log n) |
| Quick Sort       | average n log n | O(n log n) |
| Ford–Johnson     | **minimum theoretical comparisons** | O(n log n) |

 Ford–Johnson is optimal in terms of **comparison count**, not just runtime.

---

## ⏱ Performance Measurement

You must measure:
- parsing time
- sorting time
- container-specific overhead

Comparison is required between:
- Container 1 (commonly `vector`)
- Container 2 (commonly `deque`)

This highlights:
- memory locality
- insertion cost
- cache efficiency

---

## Summary

This module teaches:

- Real-world data parsing
- Stack-based computation systems
- Advanced sorting algorithm design
- Performance analysis between STL containers
- Algorithmic optimization beyond Big-O notation

