#pragma once
#include "Node.hpp"

class BST {
public:
    BST() : root(nullptr), insertComparisons(0), searchComparisons(0) {}
    void insert(int key);
    Node* iterativeInsert(int key);
    bool search(int key);
    Node* iterativeSearch(int key);
    int getInsertComparisons() const { return insertComparisons; }
    int getSearchComparisons() const { return searchComparisons; }
    void sumInsertComparisons(int sum){ insertComparisons += sum;}
    void sumSearchComparisons(int sum){ searchComparisons += sum;}
    Node* getRoot() {return this->root;}
    void setRoot(Node *root) {this->root = root;}

private:
    Node* root = nullptr;
    int insertComparisons = 0;
    int searchComparisons = 0;
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

Node* BST::iterativeInsert(int key){
    Node* node = getRoot();
//    std::cout << "aqui" << std::endl;

    sumInsertComparisons(1);                // Contar comparações com o nulo?
    if(node == nullptr){
        setRoot(new Node(key, 0)); 
        return getRoot();
    }

    int level = 1;    
    Node* aux = new Node(key);
    backInsert:
    if(node->key < key){
        sumInsertComparisons(1);
        if (node->right == nullptr){
            node->right = aux;
            aux->father = node;
            aux->level = level;
            return aux;
        }
        else{
            node = node->right;
            level++;
            goto backInsert;
        }
    }
    else{
        sumInsertComparisons(1);
        if (node->left == nullptr){
            node->left = aux;
            aux->father = node;
            aux->level = level;
            return aux;
        }
        else{
            node = node->left;
            level++;
            goto backInsert;
        }
    }
}

Node* BST::iterativeSearch(int key){
    Node* node = getRoot();

    sumSearchComparisons(1);
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