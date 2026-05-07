//
// Created by Ксения on 04.05.2026.
//

#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <fstream>
#include <string>

namespace trees {

    template <typename T>
    class BSTree {
    private:
        struct Node {
            T data;
            Node* left;
            Node* right;
            Node(const T& val);
        };

        Node* root;

        void clear(Node* node);
        Node* copy(Node* node);
        Node* insert(Node* node, const T& val);
        Node* findMin(Node* node);
        Node* remove(Node* node, const T& val, bool& removed);
        bool search(Node* node, const T& val) const;
        void preOrder(Node* node, std::ostream& os) const;
        void inOrder(Node* node, std::ostream& os) const;
        void postOrder(Node* node, std::ostream& os) const;
        void save(Node* node, std::ofstream& ofs) const;
        Node* load(std::ifstream& ifs);

    public:
        BSTree();
        BSTree(const BSTree& other);
        BSTree(BSTree&& other) noexcept;
        ~BSTree();

        BSTree& operator=(const BSTree& other);
        BSTree& operator=(BSTree&& other) noexcept;

        void add(const T& val);
        bool remove(const T& val);
        void clearTree();
        bool find(const T& val) const;

        void printPreOrder(std::ostream& os = std::cout) const;
        void printInOrder(std::ostream& os = std::cout) const;
        void printPostOrder(std::ostream& os = std::cout) const;

        bool saveToFile(const std::string& filename) const;
        bool loadFromFile(const std::string& filename);

        friend std::ostream& operator<<(std::ostream& os, const BSTree<T>& tree) {
            tree.printInOrder(os);
            return os;
        }
    };

}

#endif