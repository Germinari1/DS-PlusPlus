# DS-PlusPlus
A collection of custom-implemented data structures in C++. The data structures in this repository were created from scratch and first implemented for learning purposes. 

## Features
This repository contains the following data structures:
- `AVL tree`
- ``Hash table``
- ``Graph``
- ``Queue``
- ``Priority queue``
- ``Stack``
- ``Vector``
- ``Map``
- ``Set``
- ``Doubly Linked List``

<br>

Those data structures provide users with the opportunity to analyze possible implementations of widely used DSA concepts, as well as modify and play around with them.

## Quick start and usage
1. Download the repository from GitHub
2. Place the folder with the implementations in the desired working repository
3. In your C++ code, it is possible to include a particular data structure like this (using hashTable as example):
```cpp
#include "hashTable.h"
```
To use the data structure, then, a user can instantiate the corresponding objects and perform associated operations (add data, retrieve an item, etc) in the following way (again, using hashTable as an example)
```cpp
#include <iostream>
#include <string>
#include "hashTable.h"

int main() {
    // Create a hash table with string keys and integer values
    HashTable<std::string, int> hashTable;

    // Insert key-value pairs
    hashTable.insert("apple", 5);
    hashTable.insert("banana", 10);
    hashTable.insert("cherry", 15);

    // Check size
    std::cout << "Size of hash table: " << hashTable.getSize() << std::endl;

    return 0
}
```
