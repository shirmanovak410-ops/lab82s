#include "../include/BSTree.hpp"
#include <iostream>

int main() {
    using namespace trees;

    BSTree<int> tree;

    tree.add(50);
    tree.add(30);
    tree.add(70);
    tree.add(20);
    tree.add(40);
    tree.add(60);
    tree.add(80);

    std::cout << "In-order: ";
    tree.printInOrder();
    std::cout << std::endl;

    std::cout << "Pre-order: ";
    tree.printPreOrder();
    std::cout << std::endl;

    std::cout << "Post-order: ";
    tree.printPostOrder();
    std::cout << std::endl;

    std::cout << "Tree: " << tree << std::endl;

    std::cout << "Find 40: " << tree.find(40) << std::endl;
    std::cout << "Find 100: " << tree.find(100) << std::endl;

    tree.remove(30);
    std::cout << "After remove 30: " << tree << std::endl;

    if (tree.saveToFile("tree.txt")) {
        std::cout << "Saved to tree.txt" << std::endl;
    }

    BSTree<int> tree2;
    if (tree2.loadFromFile("tree.txt")) {
        std::cout << "Loaded: " << tree2 << std::endl;
    }

    BSTree<int> tree3(tree2);
    std::cout << "Copy: " << tree3 << std::endl;

    BSTree<int> tree4(std::move(tree3));
    std::cout << "Move: " << tree4 << std::endl;

    tree4.clearTree();
    std::cout << "After clear: " << tree4 << std::endl;

    return 0;
}