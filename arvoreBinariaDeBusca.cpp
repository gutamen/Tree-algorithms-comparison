#include <iostream>
#include <fstream>
#include <chrono>
#include "BST.hpp"

/*struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

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
*/

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Erro: Use " << argv[0] << " <arquivo_construcao> <arquivo_consulta>" << std::endl;
        return 1;
    }

    std::ifstream constructionFile(argv[1]);
    std::ifstream queryFile(argv[2]);

    if (!constructionFile.is_open() || !queryFile.is_open()) {
        std::cerr << "Error opening file(s)." << std::endl;
        return 1;
    }

    BST tree;
    int key;

    // Construção da árvore
    auto startConstruction = std::chrono::high_resolution_clock::now();
    while (constructionFile >> key) {
        tree.insert(key);
    }
    auto endConstruction = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedConstruction = endConstruction - startConstruction;

    std::cout << "Nuemro de comapracoes na insercao: " << tree.getInsertComparisons() << std::endl;
    std::cout << "Tempo na construcao da arvore: " << elapsedConstruction.count() << " secs" << std::endl;

    // Consulta na árvore
    int totalSearchComparisons = 0;
    auto startSearch = std::chrono::high_resolution_clock::now();
    while (queryFile >> key) {
        tree.search(key);
        totalSearchComparisons += tree.getSearchComparisons();
    }
    auto endSearch = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedSearch = endSearch - startSearch;

    std::cout << "Numero de comparacoes na busca: " << totalSearchComparisons << std::endl;
    std::cout << "Tempo na busca: " << elapsedSearch.count() << " secs" << std::endl;

    constructionFile.close();
    queryFile.close();

    return 0;
}

