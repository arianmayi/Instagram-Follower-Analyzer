//
// Created by arian on 10/15/2026.
//

#ifndef PROJECT2_RED_BLACK_H
#define PROJECT2_RED_BLACK_H



struct Node {
    int data;
    bool color; // true for red, false for black
    Node *left;
    Node *right;
    Node *parent;

    Node(int data) : data(data), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node *root;

public:
    //Constructor
    RedBlackTree();
    //Rotate functions
    void rotateLeft(Node *&node);
    void rotateRight(Node *&node);
    //Inserting new nodes
    void insert(const int &data);
    //Balance the tree after insertion
    void insertFixup(Node *&node);
    
    
};



//stores data in red-black tree

#endif