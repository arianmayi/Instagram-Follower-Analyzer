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

public:
    //Constructor
    RedBlackTree();
    //Rotate functions
    void rotateLeft(Node *node);
    void rotateRight(Node *node);
    //Inserting new nodes
    void insert(const string &username);
    //Balance the tree after insertion
    void insertFixup(Node *node);
    void printTree(Node *root);
    bool containsUser(const string &username);
};



//stores data in red-black tree

#endif