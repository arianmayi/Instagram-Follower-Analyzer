//
// Created by arian on 10/15/2026.
//

#ifndef PROJECT2_RED_BLACK_H
#define PROJECT2_RED_BLACK_H

//stores data in red-black tree

void RedBlackTree::RedBlackTree() {
    root = nullptr;
}

void RedBlackTree::rotateLeft(Node *&node) {
    Node *rightChild = node->right;
    node->right = rightChild->left;

    if (node->right != nullptr) {
        node->right->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(Node *&node) {
    Node *leftChild = node->left;
    node->left = leftChild->right;

    if (node->left != nullptr) {
        node->left->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

void RedBlackTree::insert(const int &data) {
    Node *newNode = new Node(data);
    if (root == nullptr) {
        root = newNode;
        root->color = false; // Root is always black
        return;
    }

    Node *parent = nullptr;
    Node *current = root;

    while (current != nullptr) {
        parent = current;
        if (newNode->data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;

    if (newNode->data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    insertFixup(newNode);
}
void RedBlackTree::insertFixup(Node *&node) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;
    Node* current = node;
    if (node == root) {
        node->color = false; // Root is always black
        return;
    }
    //Implement rotations and color switches to maintain red-black properties
    
    
}

#endif //PROJECT2_RED_BLACK_H
