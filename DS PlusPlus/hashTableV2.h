/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//* Author: Lucas Germinari Carreira
//* Last update: 04/25/2024
//* Description(data structure implementation): This file contains the implementation of a hashTableV2 that allows for custom, user-defined hash function
//* Tested: yes, passed
//* Notes:
//*    - The hashTableV2 is implemented using separate chaining to handle collisions.
//*    - The hash function is provided by the user as a template parameter.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#pragma once

//* HEADER FILES
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "myVector.h"

//* HT2_Node structure for the hashTableV2
template <typename T>
struct HT2_Node {
    T value;
    HT2_Node<T>* next;

    HT2_Node(const T& val) : value(val), next(nullptr) {}
};

//* HashTableV2 class
template <typename T, typename HashFunc>
class HashTableV2 {
private:
    HT2_Node<T>** buckets; // array of pointers to linked lists
    size_t bucket_count;  // number of buckets
    size_t size;          // number of elements
    HashFunc hashFunc;    // User-provided hash function

    // Hash function to hashTableV2 elements to bucket indices
    size_t hashCode(const T& value) const {
        // Use the user-provided hash function
        return hashFunc(value) % bucket_count;
    }

public:
    // Constructor
    HashTableV2(size_t bucket_count, HashFunc hash_func)
        : bucket_count(bucket_count), size(0), hashFunc(hash_func) {
        buckets = new HT2_Node<T>*[bucket_count];
        for (size_t i = 0; i < bucket_count; ++i) {
            buckets[i] = nullptr;
        }
    }

    // Destructor
    ~HashTableV2() {
        clear();
        delete[] buckets;
    }

    // Display the contents of the HashTableV2
    void displayContents() const {
        std::cout << "Hash Table Contents:" << std::endl;
        for (size_t i = 0; i < bucket_count; ++i) {
            std::cout << "Index " << i << ": ";
            HT2_Node<T>* entry = buckets[i];
            if (entry == nullptr) {
                std::cout << "Empty" << std::endl;
            } else {
                while (entry != nullptr) {
                    std::cout << entry->value << " ";
                    entry = entry->next;
                }
                std::cout << std::endl;
            }
        }
    }

    // Clear the hashTableV2
    void clear() {
        for (size_t i = 0; i < bucket_count; ++i) {
            HT2_Node<T>* entry = buckets[i];
            while (entry != nullptr) {
                HT2_Node<T>* prev = entry;
                entry = entry->next;
                delete prev;
            }
            buckets[i] = nullptr;
        }
        size = 0;
    }

    // Insert an element
    void insert(const T& value) {
        size_t index = hashCode(value);
        HT2_Node<T>* prev = nullptr;
        HT2_Node<T>* entry = buckets[index];

        while (entry != nullptr) {
            prev = entry;
            entry = entry->next;
        }

        entry = new HT2_Node<T>(value);
        if (prev == nullptr) {
            buckets[index] = entry;
        } else {
            prev->next = entry;
        }
        ++size;
    }

    // Check if an element exists in the hashTableV2
    bool contains(const T& value) const {
        size_t index = hashCode(value);
        HT2_Node<T>* entry = buckets[index];

        while (entry != nullptr) {
            if (entry->value == value) {
                return true;
            }
            entry = entry->next;
        }
        return false;
    }

    // Check if an element exists in the hashTableV2
    T* getElement(T& value) const {
        size_t index = hashCode(value);
        HT2_Node<T>* entry = buckets[index];

        while (entry != nullptr) {
            if (entry->value == value) {
                return &(entry->value); // Return a pointer to the found element
            }
            entry = entry->next;
        }
        return nullptr; // Return nullptr if not found
    }

    // Remove an element
    void remove(const T& value) {
        size_t index = hashCode(value);
        HT2_Node<T>* prev = nullptr;
        HT2_Node<T>* entry = buckets[index];

        while (entry != nullptr && entry->value != value) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            return; // Element not found
        }

        if (prev == nullptr) {
            buckets[index] = entry->next;
        } else {
            prev->next = entry->next;
        }

        delete entry;
        --size;
    }

    // Get the size of the hashTableV2
    size_t getSize() const {
        return size;
    }

    // Get all elements in the hashTableV2
    MyVector<T> getElements() const {
        MyVector<T> elements;
        for (size_t i = 0; i < bucket_count; ++i) {
            HT2_Node<T>* entry = buckets[i];
            while (entry != nullptr) {
                elements.push_back(entry->value);
                entry = entry->next;
            }
        }
        return elements;
    }
};