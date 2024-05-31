
#include <cstddef>
class node{
    
    private:
    node *left = NULL, *right = NULL, *father = NULL;
    int balance = 0;
    int nodeRelativeHeight = 0;
    double data;

    public:   
    node(double data){
        this -> data = data;
    }

    void setLeftSon(node *son){
        this -> left = son;
    }

    void setRightSon(node *son){
        this -> right = son;
    }

    void setFather(node *father){
        this -> father = father;
    }

};
