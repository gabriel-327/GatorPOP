# GatorPop

## Description
GatorPop project is a c++ application that implements and compares two sorting algorithms, which are  Merge Sort and Heap Sort to sort a dataset of 100,000 songs by release dates. By comparing the performance and complexity of these sorting algorithms, this project aims to demonstrate the trade-offs between these two popular sorting methods, especially when handling large datasets.

## Features

### Merge Sort
- Implements a stable, divide-and-conquer sorting algorithm with consistent **O(n log n)** performance.
- Splits the dataset into smaller parts, recursively sorts each part, and merges them back together in sorted order.

### Heap Sort
- Utilizes an in-place, binary heap data structure for sorting, achieving **O(n log n)** performance without requiring additional memory for merging.
- Efficient in terms of space usage but does not maintain the relative order of duplicate entries.

### Dataset Sorting by Release Date
- Sorts a large dataset of song release dates to test and compare the performance of each algorithm.
