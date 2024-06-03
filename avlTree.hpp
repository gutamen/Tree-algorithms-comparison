#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include "BST.hpp"


class AVLTree : public BST{
    
    private:
    long long balanceComparisons = 0;

    public:
    long long getBalanceComparisons() const { return balanceComparisons; }
    void sumBalanceComparisons(long long sum){ balanceComparisons += sum;}

    Node* iterativeInsert(int key){
        Node* node = BST::iterativeInsert(key);
        balanceTree(node);  
        return node;
    }


    int getBalance(Node* node) {
        sumBalanceComparisons(3);
        if (node == nullptr) {
            std::cout << "é nulo" << std::endl;
            return 0;
        }
        int rightHeight = node->right == nullptr ? 0 : nodeMaxLevel(node->right) - node->level;
        int leftHeight = node->left == nullptr ? 0 : nodeMaxLevel(node->left) - node->level;
        return rightHeight - leftHeight;
    }

    void balanceTree(Node* node) {
        
        while (node != nullptr) {
            //node->level = height(node);  // Atualiza a altura do nó
            int balance = getBalance(node);
//            std::cout << balance << std::endl;
            sumBalanceComparisons(1);
            if (balance > 1) {
//                std::cout << "Balance" << std::endl;
                sumBalanceComparisons(1);
                if (getBalance(node->right) < 0) {
                    node->right = rotateRight(node->right);
                }
                node = rotateLeft(node);
            } 
            else if (balance < -1) {  
                sumBalanceComparisons(2);
//                std::cout << "Balance" << std::endl;
                if (getBalance(node->left) > 0) {
                    node->left = rotateLeft(node->left);
                }
                node = rotateRight(node);
            }

            node = node->father;
        }
    }

    Node* rotateRight(Node* node) {
        int actualLevel = node->level;
//        std::cout << node->key << std::endl;
        Node* x = node->left;
        Node* T2 = x->right;

        x->right = node;
        node->left = T2;

        sumBalanceComparisons(3);
        if (T2 != nullptr) {
            T2->father = node;
        }

        x->father = node->father;
        node->father = x;

        node->level = actualLevel + 1;
        x->level = actualLevel;

        updateLevels(node);
        updateLevels(x);
        /*
        if(node->right != nullptr){
            node->right->level = node->level + 1;
        } 
        if(node->left != nullptr){
            node->left->level = node->level + 1;
        } 

        if(x->right != nullptr){ 
            x->right->level = x->level + 1;
        }

        if(x->left != nullptr){
            x->left->level = x->level + 1;
        }
        */

        
        if (x->father != nullptr) {
            if (x->father->left == node) {
                x->father->left = x;
            } else {
                x->father->right = x;
            }
        } else {
            setRoot(x);
        }

        return x;
    }

    Node* rotateLeft(Node* node) {
        int actualLevel = node->level;
//        std::cout << node->key << std::endl;
        Node* y = node->right;
        Node* T2 = y->left;

        y->left = node;
        node->right = T2;

        sumBalanceComparisons(3);
        if (T2 != nullptr) {
            T2->father = node;
        }

        y->father = node->father;
        node->father = y;

        node->level = actualLevel + 1;
        y->level = actualLevel;

        updateLevels(node);
        updateLevels(y);
        /*
        if(node->right != nullptr) node->right->level = node->level + 1;
        if(node->left != nullptr) node->left->level = node->level + 1;

        if(y->right != nullptr) y->right->level = y->level + 1;
        if(y->left != nullptr) y->left->level = y->level + 1;
        */

        if (y->father != nullptr) {
            if (y->father->left == node) {
                y->father->left = y;
            } else {
                y->father->right = y;
            }
        } else {
            setRoot(y);
        }

        return y;
    }


    void updateLevels(Node* node) {
        sumBalanceComparisons(1);
        if (node == nullptr) return;

        std::queue<Node*> queue;
        queue.push(node);


        while (!queue.empty()) {
            Node* current = queue.front();
            queue.pop();
            if (current->left != nullptr) {
                current->left->level = current->level + 1;
                queue.push(current->left);
            }
            
            if (current->right != nullptr) {
                current->right->level = current->level + 1;
                queue.push(current->right);
            }
            sumBalanceComparisons(3);
        }
    }

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
                sumBalanceComparisons(1);
            }     
            currentNode = treeStack.top();
            treeStack.pop();
            
            sumBalanceComparisons(1);
            if(currentNode->level > maxLevel){
                maxLevel = currentNode->level;
            }
            
            currentNode = currentNode->right;
            sumBalanceComparisons(1);
        } 

        return maxLevel;
    }

};
