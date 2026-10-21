//
// Created by arian on 10/15/2026.
//

#include "Red_Black.h"

struct Node {
    int data;
    bool color; // true for red, false for black
    Node *left;
    Node *right;
    Node *parent;

    Node(int data) : data(data), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
};
//DO NOT DELETE UNTIL NEAR END OF PROJECT - USE AS GUIDE

/*
 *Vitor's part
 *Red-Black implantation, where the data will be stored
 *
 *
 */
class RedBlackTree {
private:
    Node *root;

public:
    //Constructor
    void RedBlackTree();
    //Rotate functions
    void rotateLeft(Node *&node);
    void rotateRight(Node *&node);
    //Inserting new nodes
    void insert(const int &data);
    //Balance the tree after insertion
    void insertFixup(Node *&node);
    
    
};
