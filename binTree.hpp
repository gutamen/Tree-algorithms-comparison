#include "node.hpp"

class binTree{
    private:
    node *root = NULL;
    int height = 0;

    public:
    binTree(node *root){
        this -> root = root; 
    }

    binTree(double data){
        this -> root = new node(data);
    }


};
