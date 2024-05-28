/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//* Author: Lucas Germinari Carreira
//* Last modification date: 04/08/2024
//* Description(Data structure implementation): MapV1 implementation
//* Tested: yes, passed
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

#pragma once
//HEADER FILES
#include <iostream>
#include <string>
#include <utility> // for std::pair

// MapV1Node structure for the mapV1
template <typename K, typename V>
struct MapV1Node {
    std::pair<K, V> pair;
    MapV1Node<K, V>* next;

    MapV1Node(const K& key, const V& value) : pair(key, value), next(nullptr) {}
};

// MapV1 class
template <typename K, typename V>
class MapV1 {
private:
    MapV1Node<K, V>** buckets; // array of pointers to linked lists
    size_t bucket_count;  // number of buckets
    size_t size;          // number of key-value pairs

    // Hash function to mapV1 keys to bucket indices
    size_t hashCode(const K& key) const {
        // Simple hash function for demonstration purposes
        return std::hash<K>{}(key) % bucket_count;
    }

public:
    // Constructor
    MapV1(size_t bucket_count = 100) : bucket_count(bucket_count), size(0) {
        buckets = new MapV1Node<K, V>*[bucket_count];
        for (size_t i = 0; i < bucket_count; ++i) {
            buckets[i] = nullptr;
        }
    }

    // Destructor
    ~MapV1() {
        clear();
        delete[] buckets;
    }

    // Clear the mapV1
    void clear() {
        for (size_t i = 0; i < bucket_count; ++i) {
            MapV1Node<K, V>* entry = buckets[i];
            while (entry != nullptr) {
                MapV1Node<K, V>* prev = entry;
                entry = entry->next;
                delete prev;
            }
            buckets[i] = nullptr;
        }
        size = 0;
    }

    // Insert a key-value pair (or updates, if already exists)
    void insert(const K& key, const V& value) {
        size_t index = hashCode(key);
        MapV1Node<K, V>* prev = nullptr;
        MapV1Node<K, V>* entry = buckets[index];

        while (entry != nullptr && entry->pair.first != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            entry = new MapV1Node<K, V>(key, value);
            if (prev == nullptr) {
                buckets[index] = entry;
            } else {
                prev->next = entry;
            }
            ++size;
        } else {
            // Key already exists, update the value
            entry->pair.second = value;
        }
    }

    // Get the value associated with a key
    V& get(const K& key) {
        size_t index = hashCode(key);
        MapV1Node<K, V>* entry = buckets[index];

        while (entry != nullptr && entry->pair.first != key) {
            entry = entry->next;
        }

        if (entry == nullptr) {
            throw std::out_of_range("Key not found");
        }

        return entry->pair.second;
    }

    // Check if a key exists in the mapV1
    bool contain_key(const K& key){
        size_t index = hashCode(key);
        MapV1Node<K, V>* entry = buckets[index];

        while(entry != nullptr && entry->pair.first != key){
            entry = entry->next;
        }

        return entry != nullptr;
    }

    // Check if a value exists in the mapV1 (alternative approach)
    bool contains_value(const V& value) const {
        for (size_t i = 0; i < bucket_count; ++i) {
            MapV1Node<K, V>* entry = buckets[i];
            while (entry != nullptr) {
                if (entry->pair.second == value) {
                    return true;
                }
                entry = entry->next;
            }
        }
        return false;
    }


    //overloading []
    V& operator[](const K& key){
        return get(key);
    }

    // Remove a key-value pair
    void remove(const K& key) {
        size_t index = hashCode(key);
        MapV1Node<K, V>* prev = nullptr;
        MapV1Node<K, V>* entry = buckets[index];

        while (entry != nullptr && entry->pair.first != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            return; // Key not found
        }

        if (prev == nullptr) {
            buckets[index] = entry->next;
        } else {
            prev->next = entry->next;
        }

        delete entry;
        --size;
    }

    // Get the size of the mapV1
    size_t getSize() const {
        return size;
    }
};