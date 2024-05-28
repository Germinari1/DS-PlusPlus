/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//* Author: Lucas Germinari Carreira
//* Last modification date: 04/15/2024
//* Description (data structure implementation): Implements a AVL tree 
//* Tested: yes, passed (tested with integers)
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#include <iostream>
#include <queue>
#include <string>

// Define the node structure
template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    int height;  // New field to store the height of the node

    Node(const T& value) : data(value), left(nullptr), right(nullptr), height(0) {}
};

// Define the AVL tree class
template <typename T>
class AVLTree {
private:
    Node<T>* root;

// Public interface
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { deleteTree(root); }

    Node<T>* getRoot() { return root; }
    void insert(const T& value) { root = insertNode(root, value); }
    bool search(const T& value) { return searchNode(root, value); }
    void remove(const T& value) { root = removeNode(root, value); }
    void preOrder() { preOrderTraversal(root); }
    void inOrder() { inOrderTraversal(root); }
    void postOrder() { postOrderTraversal(root); }
    void levelOrder() { levelOrderTraversal(root); }
    int getHeight() { return height(root); }
    int getDepth(T& value) { return depth(root, value); }
    int getSize() { return size(root); }
    AVLTree<T> deepCopy() {
        AVLTree<T> copiedTree;
        copyTree(copiedTree.root, root);
        return copiedTree;
    }
    int getNumLeaves() { return countLeaves(root); }
    bool isEmpty() { return root == nullptr; }

// Protected methods
protected:
    int countLeaves(Node<T>* node) {
        if (!node) {
            return 0;
        }

        if (!node->left && !node->right) {
            return 1;
        }

        int leftLeaves = countLeaves(node->left);
        int rightLeaves = countLeaves(node->right);

        return leftLeaves + rightLeaves;
    }

    void copyTree(Node<T>* &copiedRoot, Node<T>* otherRoot) {
        if (otherRoot == nullptr) {
            copiedRoot = nullptr;
        } else {
            copiedRoot = new Node<T>(otherRoot->data);
            copiedRoot->data = otherRoot->data;
            copiedRoot->height = otherRoot->height;
            copyTree(copiedRoot->left, otherRoot->left);
            copyTree(copiedRoot->right, otherRoot->right);
        }
    }

    int height(Node<T>* node) {
        if (!node) {
            return -1;
        }

        return node->height;
    }

    int depth(Node<T>* node, const T& value) {
        if (!node) {
            return -1;
        }

        if (node->data == value) {
            return 0;
        }

        int leftDepth = depth(node->left, value);
        if (leftDepth != -1) {
            return leftDepth + 1;
        }

        int rightDepth = depth(node->right, value);
        if (rightDepth != -1) {
            return rightDepth + 1;
        }

        return -1;
    }

    int size(Node<T>* node) {
        if (!node) {
            return 0;
        }

        int leftSize = size(node->left);
        int rightSize = size(node->right);

        return leftSize + rightSize + 1;
    }

    Node<T>* findMin(Node<T>* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void deleteTree(Node<T>* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void preOrderTraversal(Node<T>* node) {
        if (node) {
            std::cout << node->data << " ";
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    void inOrderTraversal(Node<T>* node) {
        if (node) {
            inOrderTraversal(node->left);
            std::cout << node->data << " ,";
            inOrderTraversal(node->right);
        }
    }

    void postOrderTraversal(Node<T>* node) {
        if (node) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            std::cout << node->data << " ";
        }
    }

    void levelOrderTraversal(Node<T>* node) {
        if (!node) {
            return;
        }

        std::queue<Node<T>*> queue;
        queue.push(node);

        while (!queue.empty()) {
            Node<T>* current = queue.front();
            queue.pop();
            std::cout << current->data << " ";

            if (current->left) {
                queue.push(current->left);
            }

            if (current->right) {
                queue.push(current->right);
            }
        }
    }

    bool searchNode(Node<T>* node, const T& value) {
        while (node != nullptr) {
            if (node->data == value) {
                return true;  // Value found
            } else if (value < node->data) {
                if (node->left == nullptr) {
                    return false;  // Value not found in the left subtree
                }
                node = node->left;
            } else {
                if (node->right == nullptr) {
                    return false;  // Value not found in the right subtree
                }
                node = node->right;
            }
        }
        return false;  // Value not found in the entire tree
    }

    int getBalanceFactor(Node<T>* node) {
        if (!node) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return leftHeight - rightHeight;
    }

    Node<T>* rotateLeft(Node<T>* node) {
        Node<T>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        node->height = std::max(height(node->left), height(node->right)) + 1;
        newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;

        return newRoot;
    }

    Node<T>* rotateRight(Node<T>* node) {
        Node<T>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        node->height = std::max(height(node->left), height(node->right)) + 1;
        newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;

        return newRoot;
    }

    Node<T>* insertNode(Node<T>* node, const T& value) {
        if (!node) {
            return new Node<T>(value);
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value);
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;

        int balanceFactor = getBalanceFactor(node);

        // Left Left Case
        if (balanceFactor > 1 && value < node->left->data) {
            return rotateRight(node);
        }

        // Right Right Case
        if (balanceFactor < -1 && value > node->right->data) {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balanceFactor > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balanceFactor < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node<T>* removeNode(Node<T>* node, const T& value) {
        if (!node) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = removeNode(node->left, value);
        } else if (value > node->data) {
            node->right = removeNode(node->right, value);
        } else {
            // Node with no child or only one child
            if (!node->left) {
                Node<T>* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node<T>* temp = node->left;
                delete node;
                return temp;
            } else {
                // Node with two children
                Node<T>* temp = findMin(node->right);
                node->data = temp->data;
                node->right = removeNode(node->right, temp->data);
            }
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;

        int balanceFactor = getBalanceFactor(node);

        // Left Left Case
        if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        // Right Right Case
        if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
};