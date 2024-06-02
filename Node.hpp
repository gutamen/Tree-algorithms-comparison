struct Node {
    int key;
    int balance;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr), balance(0) {}
    Node(int k, int balance) : key(k), left(nullptr), right(nullptr), balance(balance) {}
};
