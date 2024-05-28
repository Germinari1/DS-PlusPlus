/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//* Author: Lucas Germinari Carreira
//* Last modification date: 04/08/2024
//* Description(Data structure implementation): Priority queue implementation
//* Tested: yes, passed
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

#include <iostream>
#include <string>
#include <functional>

using namespace std;

//! DOUBLY LINKED LIST PRIORITY QUEUE IMPLEMENTATION
template <class T>
class QueueLL {
private:
    struct Node {
        T data;
        int priority;
        Node* next;
        Node* prev;
        Node(const T& data, int priority) : data(data), priority(priority), next(nullptr), prev(nullptr) {}
    };

    Node* front;
    Node* rear;
    size_t listSize;
    int max_size;

public:
    // Constructor
    QueueLL(int max_s = 0) : front(nullptr), rear(nullptr), listSize(0), max_size(max_s) {}

    // Destructor
    ~QueueLL() {
        Node* current = front;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    bool isFull() {
        if (max_size == 0) {
            return false;
        }
        return listSize == max_size;
    }

    // Enqueue an element with a priority
    void enqueue(const T& data, int priority) {
        Node* newNode = new Node(data, priority);

        // If the queue is empty or the new node has higher priority than the front
        if (front == nullptr || newNode->priority > front->priority) {
            newNode->next = front;
            if (front != nullptr) {
                front->prev = newNode;
            }
            front = newNode;
        } else {
            Node* current = front;
            while (current->next != nullptr && current->next->priority >= newNode->priority) {
                current = current->next;
            }
            newNode->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = newNode;
            } else {
                rear = newNode;
            }
            current->next = newNode;
            newNode->prev = current;
        }
        listSize++;
    }

    void destroy() {
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

    void initialize_list() {
        destroy();
    }

    Node* front_peek() {
        return front;
    }

    bool search(const T& data) {
        Node* current = front;
        while (current != nullptr) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    Node* rear_peek() {
        return rear;
    }

    // Dequeue the element with the highest priority
    void dequeue() {
        if (front == nullptr) {
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front != nullptr) {
            front->prev = nullptr;
        } else {
            rear = nullptr;
        }
        delete temp;
        listSize--;
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
            cout << "(" << current->data << ", " << current->priority << ") ";
            current = current->next;
        }
        cout << endl;
    }
};