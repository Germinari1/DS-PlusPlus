/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//* Author: Lucas Germinari Carreira
//* Last modification date: 04/08/2024
//* Description(Data structure implementation): Protected dynamic array implementation
//* Tested: yes, passed
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

#include <iostream>
#include <string>

using namespace std;


template <class T>
class TemplateArray {
private:
    T *array;
    int size;
    int capacity;

public:
    //constructor
    TemplateArray(int size=100){
        //check size
        if(size <=0){
            throw invalid_argument("Size must be greater than 0");
        }
        //allocate memory  for array
        array = new T[size];
        this->size = size;
    }
    //free memory
    ~TemplateArray(){
        delete[] array;
    }

    int getSize(){
        return size;
    }

    //safe indexing with bounds checking
    T getValue(int index){
        if(index < 0 || index >= size){
            throw out_of_range("Index out of range");
        }
        return array[index];
    }
    void setValue(int index, T value){
        if(index < 0 || index >= size){
            throw out_of_range("Index out of range");
        }
        array[index] = value;
    }

    void resize(int newSize) {
        if (newSize <= 0) {
            throw invalid_argument("Size must be greater than 0");
        }

        T* newArray = new T[newSize];

        // Copy existing elements to the new array
        int copySize = (newSize < size) ? newSize : size;
        for (int i = 0; i < copySize; i++) {
            newArray[i] = array[i];
        }

        // Deallocate the old array
        delete[] array;

        array = newArray;
        size = copySize;
        capacity = newSize;
    }

    //overload [] operator
    T& operator[](int index){
        if(index < 0 || index >= size){
            throw out_of_range("Index out of range");
        }
        return array[index];
    }

};