#pragma once
#include <iostream>
#include <stack>
#include "BST.hpp"


class AVLTree : public BST{
    
    public:
    Node* iterativeInsert(int key){
        Node* node = BST::iterativeInsert(key);
//        balanceTree(node);

/*        Node* aux = node;

        bool verify = false;
        while(aux != nullptr){
//            verify = balance(aux);
//            std::cout << aux->key << std::endl;   
            aux = aux->father;
        }
*/       
        return node;
    }

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = node->left ? node->left->level + 1 : 0;
        int rightHeight = node->right ? node->right->level + 1 : 0;
        return std::max(leftHeight, rightHeight);
    }

    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int rightHeight = node->right == nullptr ? 0 : nodeMaxLevel(node->right) - node->level;
        int leftHeight = node->left == nullptr ? 0 : nodeMaxLevel(node->left) - node->level;
        return rightHeight - leftHeight;
    }

    void balanceTree(Node* node) {
        //while (node != nullptr) {
            //node->level = height(node);  // Atualiza a altura do nó
            int balance = getBalance(node);
            std::cout << balance << std::endl;
            if (balance > 1) {
                std::cout << "teste" << std::endl;
                if (getBalance(node->left) < 0) {
                    node->left = rotateLeft(node->left);
                }
                node = rotateRight(node);
            } else if (balance < -1) {  
                std::cout << "teste right" << std::endl;
                if (getBalance(node->right) > 0) {
                    node->right = rotateRight(node->right);
                }
                node = rotateLeft(node);
            }

            node = node->father;
        //}
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        if (T2 != nullptr) {
            T2->father = y;
        }

        x->father = y->father;
        y->father = x;

        y->level = height(y);
        x->level = height(x);

        if (x->father != nullptr) {
            if (x->father->left == y) {
                x->father->left = x;
            } else {
                x->father->right = x;
            }
        } else {
            setRoot(x);
        }

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        if (T2 != nullptr) {
            T2->father = x;
        }

        y->father = x->father;
        x->father = y;

        x->level = height(x);
        y->level = height(y);

        if (y->father != nullptr) {
            if (y->father->left == x) {
                y->father->left = y;
            } else {
                y->father->right = y;
            }
        } else {
            setRoot(y);
        }

        return y;
    }
/*
    bool balance(Node *node){ 
        int height = 0;
        bool originBack = false; 
//        std::cout << "aqui" << std::endl;
        
        int rightHeight = node->right == nullptr ? 0 : nodeMaxLevel(node->right) - node->level;
        int leftHeight = node->left == nullptr ? 0 : nodeMaxLevel(node->left) - node->level;

        std::cout << rightHeight - leftHeight << std::endl;
        
        if(rightHeight - leftHeight > 1){       //Balanceamento Direita Positivo
            // Precisa Balancear
            if(node->right->left == nullptr && node->right->right != nullptr){
                Node *aux = node;
                node = aux->right;
                node->father = aux->father;
                Node *auxAux = node->left;
                node->left = aux;
                aux->right = auxAux;
                aux->father = node;
                if(node->father != nullptr){
                    if (node->father->right == aux){
                        node->father->right = node;
                    }
                    else{
                        node->father->left = node;
                    }
                }
                else{
                    setRoot(node);
                }

                std::cout << "aqui" << std::endl;
            }
            std::cout << "aqui teste" << std::endl;
            return true;
        }
        else if (rightHeight - leftHeight < 1){ //Balanceamento Esquerda Negativo
            // Precisa Balancear

            return true;
        }

        return false;

    }
*/

    int nodeMaxLevel(Node *node){
        int maxLevel = node->level;
        std::stack<Node*> treeStack;
        Node *currentNode = node;

        while (currentNode != NULL || treeStack.empty() == false)
        {    
            while (currentNode != NULL)
            {  
                treeStack.push(currentNode);
                currentNode = currentNode->left;
            }     
            currentNode = treeStack.top();
            treeStack.pop();
            
            if(currentNode->level > maxLevel){
                maxLevel = currentNode->level;
            }
            
            currentNode = currentNode->right;
        } 

        return maxLevel;
    }

};
