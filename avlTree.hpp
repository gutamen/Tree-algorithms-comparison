#pragma once
#include <iostream>
#include <stack>
#include "BST.hpp"


class AVLTree : public BST{
    
    public:
    Node* iterativeInsert(int key){
        Node* node = BST::iterativeInsert(key);
        
        Node* aux = node;

        bool verify = false;
        while(aux != nullptr){
//            verify = balance(aux);
//            std::cout << aux->key << std::endl;   
            aux = aux->father;
        }
        
        return node;
    }


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
                node->left = aux;
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

//                std::cout << "aqui" << std::endl;
            }
            return true;
        }
        else if (rightHeight - leftHeight < 1){ //Balanceamento Esquerda Negativo
            // Precisa Balancear

            return true;
        }

        return false;

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
