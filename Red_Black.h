//
// Created by arian on 10/15/2026.
//

#ifndef PROJECT2_RED_BLACK_H
#define PROJECT2_RED_BLACK_H
#include <string>

using namespace std;


struct Node {
    string username;
    bool color; // true for red, false for black
    Node *left;
    Node *right;
    Node *parent;

    Node(string username) : username(username), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node *root;

    //rotations
    void rotateLeft(Node* node);
    void rotateRight(Node* node);

    //fix if unbalanced (& if color is off)
    void insertFixup(Node* node);

public:
    //Constructor
    RedBlackTree();

    //Destructor
    ~RedBlackTree();

    //Inserting new nodes
    void insert(const string &username);

    //Determines if the tree contains a user
    bool containsUser(const string &username);

    //Debug tool
    void printTree(Node *root);

    //prevents copying the red-black tree to multiple objects pointing to the same node
    //which could cause a double deletion
    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator = (const RedBlackTree&) = delete;
};

#endif