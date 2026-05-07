//
// Created by Ксения on 04.05.2026.
//
#include "../include/BSTree.hpp"

namespace trees {

template <typename T>
BSTree<T>::Node::Node(const T& val) : data(val), left(nullptr), right(nullptr) {}

template <typename T>
void BSTree<T>::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::copy(Node* node) {
    if (!node) return nullptr;
    Node* newNode = new Node(node->data);
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    return newNode;
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::insert(Node* node, const T& val) {
    if (!node) return new Node(val);
    if (val < node->data)
        node->left = insert(node->left, val);
    else if (val > node->data)
        node->right = insert(node->right, val);
    return node;
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::findMin(Node* node) {
    while (node->left) node = node->left;
    return node;
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::remove(Node* node, const T& val, bool& removed) {
    if (!node) return nullptr;

    if (val < node->data)
        node->left = remove(node->left, val, removed);
    else if (val > node->data)
        node->right = remove(node->right, val, removed);
    else {
        removed = true;
        if (!node->left) {
            Node* right = node->right;
            delete node;
            return right;
        }
        if (!node->right) {
            Node* left = node->left;
            delete node;
            return left;
        }
        Node* min = findMin(node->right);
        node->data = min->data;
        node->right = remove(node->right, min->data, removed);
    }
    return node;
}

template <typename T>
bool BSTree<T>::search(Node* node, const T& val) const {
    if (!node) return false;
    if (val == node->data) return true;
    if (val < node->data) return search(node->left, val);
    return search(node->right, val);
}

template <typename T>
void BSTree<T>::preOrder(Node* node, std::ostream& os) const {
    if (!node) return;
    os << node->data << " ";
    preOrder(node->left, os);
    preOrder(node->right, os);
}

template <typename T>
void BSTree<T>::inOrder(Node* node, std::ostream& os) const {
    if (!node) return;
    inOrder(node->left, os);
    os << node->data << " ";
    inOrder(node->right, os);
}

template <typename T>
void BSTree<T>::postOrder(Node* node, std::ostream& os) const {
    if (!node) return;
    postOrder(node->left, os);
    postOrder(node->right, os);
    os << node->data << " ";
}

template <typename T>
void BSTree<T>::save(Node* node, std::ofstream& ofs) const {
    if (!node) {
        ofs << "()";
        return;
    }
    ofs << "(" << node->data;
    save(node->left, ofs);
    save(node->right, ofs);
    ofs << ")";
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::load(std::ifstream& ifs) {
    char c;
    ifs >> c;
    if (c != '(') return nullptr;

    ifs >> c;
    if (c == ')') return nullptr;

    ifs.putback(c);
    T val;
    ifs >> val;

    Node* node = new Node(val);
    node->left = load(ifs);
    node->right = load(ifs);

    ifs >> c;
    return node;
}

template <typename T>
BSTree<T>::BSTree() : root(nullptr) {}

template <typename T>
BSTree<T>::BSTree(const BSTree& other) : root(nullptr) {
    if (other.root) {
        root = copy(other.root);
    }
}

template <typename T>
BSTree<T>::BSTree(BSTree&& other) noexcept : root(other.root) {
    other.root = nullptr;
}

template <typename T>
BSTree<T>::~BSTree() {
    clear(root);
}

template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree& other) {
    if (this != &other) {
        clear(root);
        root = other.root ? copy(other.root) : nullptr;
    }
    return *this;
}

template <typename T>
BSTree<T>& BSTree<T>::operator=(BSTree&& other) noexcept {
    if (this != &other) {
        clear(root);
        root = other.root;
        other.root = nullptr;
    }
    return *this;
}

template <typename T>
void BSTree<T>::add(const T& val) {
    root = insert(root, val);
}

template <typename T>
bool BSTree<T>::remove(const T& val) {
    bool removed = false;
    root = remove(root, val, removed);
    return removed;
}

template <typename T>
void BSTree<T>::clearTree() {
    clear(root);
    root = nullptr;
}

template <typename T>
bool BSTree<T>::find(const T& val) const {
    return search(root, val);
}

template <typename T>
void BSTree<T>::printPreOrder(std::ostream& os) const {
    preOrder(root, os);
}

template <typename T>
void BSTree<T>::printInOrder(std::ostream& os) const {
    inOrder(root, os);
}

template <typename T>
void BSTree<T>::printPostOrder(std::ostream& os) const {
    postOrder(root, os);
}

template <typename T>
bool BSTree<T>::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) return false;
    save(root, ofs);
    return !ofs.fail();
}

template <typename T>
bool BSTree<T>::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return false;

    clearTree();
    root = load(ifs);
    return !ifs.fail();
}

template class BSTree<int>;

} // namespace trees