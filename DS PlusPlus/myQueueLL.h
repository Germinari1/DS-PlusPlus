/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//* Author: Lucas Germinari Carreira
//* Last modification date: 04/08/2024
//* Description(Data structure implementation): Queue implementation
//* Tested: yes, passed
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

#pragma once

#include <iostream>
#include <string>

using namespace std;

//add from rear, delete from front
//! DOUBLY LINKED LIST QUEUE IMPLEMENTATION
template <class T>
class QueueLL{
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* front;
    Node* rear;
    size_t listSize;
    int max_size;

    // Default comparison function
    //function<bool(const T&, const T&)> compare = [](const T& a, const T& b) { return a < b; };

public:
    // Constructor
    QueueLL(int max_s=0)
        : front(nullptr), rear(nullptr), listSize(0), max_size(max_s) {}

    // Destructor
    ~QueueLL() {
        Node* current = front;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    bool isFull(){
        if(max_size == 0){
            return false;
        }
        return listSize == max_size;
    }

    // Insert a new node at the end of the list
    void enqueue(const T& data) {
        Node* newNode = new Node(data);
        if(front == nullptr && rear == nullptr){
            front = newNode;
            rear = newNode;
        }
        else{
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
        listSize++;
    }

    void destroy(){
        Node* current = front;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        front = nullptr;
        rear = nullptr; 
        listSize = 0;
    }

    void initialize_list(){
        destroy();
    }

    Node* front_peek(){
        return front;
    }

    T front_peek_data(){
        return front->data;
    }  

    bool search(const T& data ){
        Node* current = front;
        while(current != nullptr){
            if(current->data == data){
                return true;
            }
            current = current->next;
    }
    return false;
    }

    Node* rear_peek(){
        return rear;
    }

    // Remove a node with the given data from the list
    void dequeue(const T& data) {
        Node* current = front;
        
        if(front == nullptr){
            return;
        }
        if(front == rear){
            front = rear = nullptr;
            listSize--;
        }
        else{
            front = front->next;
            front->prev = nullptr;
            listSize--;
        }
        delete current;
    }

    // Check if the list is empty
    bool isEmpty() const {
        return listSize == 0;
    }

    // Get the size of the list
    size_t size() const {
        return listSize;
    }

    // Print the contents of the list
    void print() const {
        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Display the contents of the queue
    void displayQueue(std::string name, bool titleOnly= false) const {
        if (isEmpty()) {
            cout << name <<" is empty." << endl;
            return;
        }

        if(titleOnly){
            cout<< name<<"\n";
            return;
        }

        Node* current = front;
        cout << name << ": ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " , ";
            }
            current = current->next;
        }
        cout << endl;
    }
};
