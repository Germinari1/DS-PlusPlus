/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//* Author: Lucas Germinari Carreira
//* Last modification date: 04/08/2024
//* Description(Data structure implementation): Set doubly-linked list implementation
//* Tested: yes, passed
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

//HEADER FILES
#include <iostream>
#include <string>

// Node struct to represent each element in the doubly-linked list
template <typename T>
struct Node {
public:
    T data;
    Node<T>* prev;
    Node<T>* next;
    Node(T value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

// Iterator class
template <typename T>
class iterator {
public:
    Node<T>* current;

public:
    iterator(Node<T>* node) : current(node) {}

    bool operator!=(const iterator& other) const {
        return current != other.current;
    }

    bool operator==(const iterator& other) const {
        return current == other.current;
    }

    T& operator*() const {
        return current->data;
    }

    iterator& operator++() {
        current = current->next;
        return *this;
    }

    iterator operator++(int) {
        iterator temp = *this;
        ++(*this);
        return temp;
    }
};

// Set class to implement the set data structure
template <typename T>
class Set {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    Set() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // Insert an element into the set
    void insert(T value) {
        // Check if the element already exists in the set (all the elements must be unique)
        if (contains(value)) {
            return;
        }

        // Create a new node and add it to the beginning of the list
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // Remove an element from the set
    void remove(T value) {
        // If the list is empty, return
        if (head == nullptr) {
            return;
        }

        // If the first element is the one to be removed
        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete temp;
            size--;
            return;
        }

        // Traverse the list and remove the element
        Node<T>* curr = head->next;
        while (curr != nullptr) {
            if (curr->data == value) {
                if (curr == tail) {
                    tail = curr->prev;
                    tail->next = nullptr;
                } else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }
                Node<T>* temp = curr;
                curr = curr->next;
                delete temp;
                size--;
                return;
            }
            curr = curr->next;
        }
    }

    // Clear set
    void clear() {
        Node<T>* curr = head;
        while (curr != nullptr) {
            Node<T>* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // Erase the element pointed to by the given iterator
    void erase(iterator<T> it) {
        // Empty set
        if (it == end()) {
            return;
        }

        // Node is head
        Node<T>* node = it.current;
        if (node == head) {
            remove(node->data);
            return;
        }

        // Node is tail
        if (node == tail) {
            tail = node->prev;
            tail->next = nullptr;
        }
        // Node in the middle
        else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        delete node;
        size--;
    }

    // Get the minimum element in the set
    T min() {
        if (head == nullptr) {
            throw std::runtime_error("Set is empty");
        }
        Node<T>* curr = head;
        T minVal = curr->data;
        while (curr != nullptr) {
            if (curr->data < minVal) {
                minVal = curr->data;
            }
            curr = curr->next;
        }
        return minVal;
    }

    // Get the maximum element in the set
    T max() {
        if (tail == nullptr) {
            throw std::runtime_error("Set is empty");
        }
        Node<T>* curr = tail;
        T maxVal = curr->data;
        while (curr != nullptr) {
            if (curr->data > maxVal) {
                maxVal = curr->data;
            }
            curr = curr->prev;
        }
        return maxVal;
    }

    // Check if an element is in the set
    bool contains(T value) {
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (curr->data == value) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    // Get the size of the set
    int getSize() {
        return size;
    }

    // Print the elements of the set
    void printSet() {
        Node<T>* curr = head;
        while (curr != nullptr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    iterator<T> begin() {
        return iterator<T>(head);
    }

    iterator<T> end() {
        return iterator<T>(nullptr);
    }

    iterator<T> find(T value) {
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (curr->data == value) {
                return iterator<T>(curr);
            }
            curr = curr->next;
        }
        return end();
    }
};