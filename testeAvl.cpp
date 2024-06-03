#include <iostream>
#include <fstream>
#include <chrono>
#include "BST.hpp"
#include "AVLTree.hpp"

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

    AVLTree tree;
    int key;

//    tree.insert(1);

//    std::cout << tree.getRoot()->key << std::endl;

    // Construção da árvore
    
    
    auto startConstruction = std::chrono::high_resolution_clock::now();
    while (constructionFile >> key) {
        tree.iterativeInsert(key);
    }
    auto endConstruction = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedConstruction = endConstruction - startConstruction;

    std::cout << "Nuemro de comapracoes na insercao: " << tree.getInsertComparisons() << std::endl;
    std::cout << "Tempo na construcao da arvore: " << elapsedConstruction.count() << " secs" << std::endl;

    std::cout << "Nuemro de comapracoes no balanceamento: " << tree.getBalanceComparisons() << std::endl;
    
    // Consulta na árvore
    
    
    int totalSearchComparisons = 0;
    auto startSearch = std::chrono::high_resolution_clock::now();
    while (queryFile >> key) {
        tree.iterativeSearch(key);
        //totalSearchComparisons += tree.getSearchComparisons();
    }
    auto endSearch = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedSearch = endSearch - startSearch;

    std::cout << "Numero de comparacoes na busca: " << tree.getSearchComparisons() << std::endl;
    std::cout << "Tempo na busca: " << elapsedSearch.count() << " secs" << std::endl;
    

    
    
    
    //tree.iterativeInsert(21);
    //std::cout << tree.getRoot()->right->right->right->left->key << std::endl;
    //std::cout << tree.getRoot()->right->right->right->left->level << std::endl;
    //tree.printTree();
    
    //tree.balanceTree(tree.getRoot()->right->right);

    //std::cout << tree.getRoot()->right->right->left->key << std::endl;
    //std::cout << tree.getRoot()->right->right->left->level << std::endl;
    //tree.printTree();

    constructionFile.close();
    queryFile.close();

    return 0;

}