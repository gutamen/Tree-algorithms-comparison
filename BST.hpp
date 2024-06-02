#pragma once
#include "Node.hpp"

class BST {
public:
    BST() : root(nullptr), insertComparisons(0), searchComparisons(0) {}
    void insert(int key);
    void iterativeInsert(int key);
    bool search(int key);
    Node* iterativeSearch(int key);
    int getInsertComparisons() const { return insertComparisons; }
    int getSearchComparisons() const { return searchComparisons; }
    void sumInsertComparisons(int sum){ insertComparisons += sum;}
    void sumSearchComparisons(int sum){ searchComparisons += sum;}
    Node* getRoot() {return this->root;}
    void setRoot(Node *root) {this->root = root;}

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

void BST::iterativeInsert(int key){
    Node* node = getRoot();
//    std::cout << "aqui" << std::endl;

//    sumInsertComparisons(1);                // Contar comparações com o nulo?
    if(node == nullptr){
        setRoot(new Node(key, 0)); 
        return;
    }

    Node* aux = new Node(key);
    backInsert:
    if(node->key > key){
        sumInsertComparisons(1);
        if (node->right == nullptr){
            node->right = aux;
            return;
        }
        else{
            node = node->right;
            goto backInsert;
        }
    }
    else{
        sumInsertComparisons(1);
        if (node->left == nullptr){
            node->left = aux;
            return;
        }
        else{
            node = node->left;
            goto backInsert;
        }
    }
}

Node* BST::iterativeSearch(int key){
    Node* node = getRoot();

    if (node == nullptr)
    {
        return nullptr;
    }

    backSearch:
    sumSearchComparisons(1);
    if (node->key == key){
        return node;
    }

    if(node->key < key){
        sumSearchComparisons(1);
        if (node->right == nullptr){
            return nullptr;
        }
        else{
            node = node->right;
            goto backSearch;
        }
    }
    else{
        sumSearchComparisons(1);
        if (node->left == nullptr){
            return nullptr;
        }
        else{
            node = node->left;
            goto backSearch;
        }
    }
}