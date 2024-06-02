#include "Node.hpp"

class BST {
public:
    BST() : root(nullptr), insertComparisons(0), searchComparisons(0) {}
    void insert(int key);
    bool search(int key);
    int getInsertComparisons() const { return insertComparisons; }
    int getSearchComparisons() const { return searchComparisons; }

private:
    Node* root;
    int insertComparisons;
    int searchComparisons;
    Node* insertRec(Node* node, int key);
    bool searchRec(Node* node, int key);
};

void BST::insert(int key) {
    root = insertRec(root, key);
}

Node* BST::insertRec(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }
    insertComparisons++;
    if (key < node->key) {
        node->left = insertRec(node->left, key);
    } else {
        node->right = insertRec(node->right, key);
    }
    return node;
}

bool BST::search(int key) {
    searchComparisons = 0; // reset counter for each search
    return searchRec(root, key);
}

bool BST::searchRec(Node* node, int key) {
    if (node == nullptr) {
        return false;
    }
    searchComparisons++;
    if (key == node->key) {
        return true;
    } else if (key < node->key) {
        return searchRec(node->left, key);
    } else {
        return searchRec(node->right, key);
    }
}