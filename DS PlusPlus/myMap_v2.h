/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//* Author: Lucas Germinari Carreira
//* Last modification date: 04/08/2024
//* Description(Data structure implementation): MapV2 implementation
//* Tested: yes, passed
//* Notes:
    - This verison supports initializations lists
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

#pragma once 

//HEADER FILES
#include <iostream>
#include <string>
#include <utility> // for std::pair

// MapNodeV2 structure for the mapV2
template <typename K, typename V>
struct MapNodeV2 {
    std::pair<K, V> pair;
    MapNodeV2<K, V>* next;

    MapNodeV2(const K& key, const V& value) : pair(key, value), next(nullptr) {}
};

// MapV2 class
template <typename K, typename V>
class MapV2 {
private:
    MapNodeV2<K, V>** buckets; // array of pointers to linked lists
    size_t bucket_count;  // number of buckets
    size_t size;          // number of key-value pairs

    // Hash function to mapV2 keys to bucket indices
    size_t hashCode(const K& key) const {
        // Simple hash function for demonstration purposes
        return std::hash<K>{}(key) % bucket_count;
    }

public:
    // Constructor
    MapV2(size_t bucket_count = 100) : bucket_count(bucket_count), size(0) {
        buckets = new MapNodeV2<K, V>*[bucket_count];
        for (size_t i = 0; i < bucket_count; ++i) {
            buckets[i] = nullptr;
        }
    }

    MapV2(std::initializer_list<std::pair<K, V>> init) : bucket_count(100), size(init.size()) {
    buckets = new MapNodeV2<K, V>*[bucket_count];
    for (size_t i = 0; i < bucket_count; ++i) {
        buckets[i] = nullptr;
    }

    for (const auto& pair : init) {
        insert(pair.first, pair.second);
    }
}

    // Destructor
    ~MapV2() {
        clear();
        delete[] buckets;
    }

    // Clear the mapV2
    void clear() {
        for (size_t i = 0; i < bucket_count; ++i) {
            MapNodeV2<K, V>* entry = buckets[i];
            while (entry != nullptr) {
                MapNodeV2<K, V>* next = entry->next;
                delete entry;
                entry = next;
            }
            buckets[i] = nullptr;
        }
        size = 0;
    }

    // Insert a key-value pair (or updates, if already exists)
    // Insert a key-value pair (or updates, if already exists)
    void insert(const K& key, const V& value) {
        size_t index = hashCode(key);
        MapNodeV2<K, V>* prev = nullptr;
        MapNodeV2<K, V>* entry = buckets[index];

        // Traverse the entire linked list to find the key or the end
        while (entry != nullptr && entry->pair.first != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            // Key not found, create a new node
            entry = new MapNodeV2<K, V>(key, value);
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
        MapNodeV2<K, V>* entry = buckets[index];

        while (entry != nullptr && entry->pair.first != key) {
            entry = entry->next;
        }

        if (entry == nullptr) {
            throw std::out_of_range("Key not found");
        }

        return entry->pair.second;
    }

    // Check if a key exists in the mapV2
    bool contain_key(const K& key){
        size_t index = hashCode(key);
        MapNodeV2<K, V>* entry = buckets[index];

        while(entry != nullptr && entry->pair.first != key){
            entry = entry->next;
        }

        return entry != nullptr;
    }

    // Check if a value exists in the mapV2 (alternative approach)
    bool contains_value(const V& value) const {
        for (size_t i = 0; i < bucket_count; ++i) {
            MapNodeV2<K, V>* entry = buckets[i];
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
        MapNodeV2<K, V>* prev = nullptr;
        MapNodeV2<K, V>* entry = buckets[index];

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

    // Get the size of the mapV2
    size_t getSize() const {
        return size;
    }
};