struct Node {
    int key;
    int balance;
    int level = 0;
    Node* left;
    Node* right;
    Node* father = nullptr;
    Node(int k) : key(k), left(nullptr), right(nullptr), balance(0) {}
    Node(int k, int balance) : key(k), left(nullptr), right(nullptr), balance(balance) {}
    Node(int k, Node *father) : key(k), left(nullptr), right(nullptr), balance(0), father(father) {}
};
