/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//* Author: Lucas Germinari Carreira
//* Last modification date: 04/08/2024
//* Description(Data structure implementation): Stack dynamic array implementation
//* Tested: yes, passed
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

#include <iostream>
#include <string>
#include "templateArray.h"
#include <numeric>
#include <limits>
//#include "dLinkedList.cpp"

//USING A DYNAMIC ARRAY   
template <class T> 
class myStackArr{
private:
    int stackSize;
    int stackTop;
    TemplateArray<T> stack;
public:
    myStackArr(int size=100, int maxSize=0): stackTop(-1), stack(size), stackSize(maxSize)  {}
    
    //empty because stack is a templateArray type, which already dealocated memory when goes out of scope
    ~myStackArr(){}

    void initializeStack(){
        stackTop = -1;
    }

    bool isEmpty() const{
        return (stackTop == -1);
    }

    bool isFull() const {
        if (stackSize == 0) {
            // Unbounded stack size, never considered full
            return false;
        } else {
            // Check if the stack top has reached the maximum size
            return (stackTop == stackSize - 1);
        }
    }

    int getSize() const {
        return stackTop + 1;
    }

    void push(const T& newItem){
        if(!isFull()){ 
            stack.setValue(++stackTop, newItem);
        }
        //undounded stack 
        else if (stackSize == 0){
            stack.resize(stack.getSize() * 2);
            stack.setValue(++stackTop, newItem);
        }
        //bounded array reached max size (avoid overflow)
        else {
            throw std::overflow_error("Stack is full");
        }        
    }

    T pop() {
    if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }

        T topValue = stack[stackTop];
        stackTop--;

        if (stackTop < stackSize / 4) {
            // Resize the underlying array if the stack is less than 1/4 full
            int newSize = (stackSize > 0) ? stackSize / 2 : stack.getSize();
            stack.resize(newSize);
            stackSize = newSize;
        }

        return topValue;
    }

    T top(){
        if(!isEmpty()){
            return stack.getValue(stackTop);
        }
        else{
            throw std::underflow_error("Stack is empty");
        }
    }

    myStackArr<T> copy() {
        myStackArr<T> newStack(stack.getSize());
        newStack.stackTop = stackTop;

        for (int i = 0; i <= stackTop; i++) {
            newStack.push(stack[i]);
        }

        return newStack;
    }
};

//USING LINKED LIST
template <class T>
class myStackLL{
private:
    int stackSize;
    DLinkedList<T> stack;

public:
    myStackLL(int size=0): stackSize(size) {}
    
    bool isEmptyStack() const{
        return stack.isEmpty();
    }

    bool isFull(){
        return (stackSize > 0 && stack.size() == stackSize);
    }

    int getSize() const{
        return stack.size();
    }

    void push(const T& newItem){
        //if stack is bounded and reached max size (overflow)
        if(stackSize > 0 && stack.size() == stackSize){
            throw std::overflow_error("Stack is full");
        }
        stack.insert(newItem);
    }

    T pop() {
        if (isEmptyStack()) {
            throw std::underflow_error("Stack is empty");
        }
        return stack.get_last();
    }

    T top() {
        if (isEmptyStack()) {
            throw std::underflow_error("Stack is empty");
        }
        return stack.get_last();
    }
};