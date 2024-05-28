/* Implements a doubly linked list */

/*NOTES 
- can traverse in both directions
- extra pointer for prev node
*/

#pragma once
#include <iostream>
#include <string>
#include <functional>

using namespace std;

template <class T>
class DLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t listSize;

    // Default comparison function
    function<bool(const T&, const T&)> compare = [](const T& a, const T& b) { return a < b; };

public:
    // Constructor
    DLinkedList(function<bool(const T&, const T&)> compare = std::less<T>())
        : head(nullptr), tail(nullptr), listSize(0), compare(compare) {}

    // Destructor
    ~DLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Insert a new node at the end of the list
    void insert(const T& data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        listSize++;
    }

    void destroy(){
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr; 
        listSize = 0;
    }

    void initialize_list(){
        destroy();
    }

    Node* get_first(){
        return head;
    } 

    bool search(const T& data ){
        Node* current = head;
        while(current != nullptr){
            if(current->data == data){
                return true;
            }
            current = current->next;
    }
    return false;
    }

    Node* get_last(){
        return tail;
    }

    // Remove a node with the given data from the list
    void remove(const T& data) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                if (current == head) {
                    head = current->next;
                    if (head != nullptr) {
                        head->prev = nullptr;
                    } else {
                        tail = nullptr;
                    }
                } else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                listSize--;
                return;
            }
            current = current->next;
        }
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
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};