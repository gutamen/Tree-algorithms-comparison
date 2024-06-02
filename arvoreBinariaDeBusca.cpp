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

