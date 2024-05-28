/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Author: Lucas Germinari Carreira
//  Date last updated: 04/28/2024
//  Description (data structure implementation): Implements a myVector.
//  Tested: no,
//  Notes:
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>

template <typename T>
class MyVector {
private:
    T* data;
    size_t capacity;
    size_t size;

public:
    // Iterator types
    using iterator = T*;
    using const_iterator = const T*;

    MyVector() : data(nullptr), capacity(0), size(0) {}
    MyVector(size_t initialCapacity) : data(new T[initialCapacity]), capacity(initialCapacity), size(0) {}
    MyVector(const MyVector& other) : capacity(other.capacity), size(other.size), data(new T[other.capacity]) {
        std::copy(other.data, other.data + other.size, data);
    }
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            std::copy(other.data, other.data + other.size, data);
        }
        return *this;
    }
    ~MyVector() { delete[] data; }

    void push_back(const T& value) {
        if (size == capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                newData[i] = std::move(data[i]);
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    size_t get_size() const { return size; }

    iterator erase(iterator it) {
        if (it < begin() || it >= end()) {
            throw std::out_of_range("MyVector::erase: iterator out of range");
        }

        iterator next = it;
        for (++next; next != end(); ++it, ++next) {
            *it = std::move(*next);
        }

        size--;
        return it;
    }

    bool empty() const { return size == 0; }
    size_t getSize() const { return size; }

    T& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("MyVector::at: index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("MyVector::at: index out of range");
        }
        return data[index];
    }

    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    iterator end() { return data + size; }
    const_iterator end() const { return data + size; }
};