//
// Created by arian on 10/15/2026.
//
#include <iostream>
#include "Red_Black.h"
#include <vector>
using namespace std;

//Constructor
RedBlackTree::RedBlackTree() {
    root = nullptr;
}

void RedBlackTree::rotateLeft(Node *node) {
    //Set up temporary variables
    Node *temp = node->right;
    node->right = temp->left;

    if(temp->left != nullptr){
        temp->left->parent = node;
    } 
    temp->parent = node->parent;

    if(node->parent == nullptr){
        root = temp;
    }
    else if(node == node->parent->left){
        node->parent->left = temp;
    }
    else {
        node->parent->right = temp;
    }

    temp->left = node;
    node->parent = temp;
}

void RedBlackTree::rotateRight(Node *node) {
    //Hold node in temporary variable
    Node *temp = node->left;
    node->left = temp->right;

    if(temp->right != nullptr){
        temp->right->parent = node;
    } 
    temp->parent = node->parent;

    if(node->parent == nullptr){
        root = temp;
    }
    else if(node == node->parent->right){
        node->parent->right = temp;
    }
    else {
        node->parent->left = temp;
    }

    temp->right = node;
    node->parent = temp;
}

void RedBlackTree::insert(const string &username) {
    Node *newNode = new Node(username);
    if(root == nullptr){
        //If first node, make it black
        root = newNode;
        root->color = false;
        return;
    }
    else {
        //Go through tree while correctly setting up parent node
        Node *parent = nullptr;
        Node *curr = root;
        while(curr != nullptr){
            parent = curr;
            if(newNode->username > curr->username){
                curr = curr->right;
                
            }
            else if(newNode->username < curr->username){
                curr = curr->left;
                
            }
            else{
                delete newNode;
                return;
            }
        }
        //Correctly insert the new node into the tree
        newNode->color = true;
        newNode->parent = parent;
        if(parent == nullptr){
            root = newNode;
        }
        else if(username < parent->username){
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
        //Fix mistakes in the tree after insertion
        //Passing the parent
        insertFixup(newNode);
    }
}

void  RedBlackTree:: insertFixup(Node *node) {

    //fix violations after insertion
    while (node != root && node->parent != nullptr && node->parent->color == true) {
        Node *parent = node->parent;
        Node *grandparent = parent->parent;

        if (grandparent == nullptr) {
            break;
        }

        //case if parent is the left child
        if (parent == grandparent->left) {

            Node *uncle = grandparent->right;

            //uncle is red (recolor)
            if (uncle != nullptr && uncle->color == true) {
                parent->color = false;
                uncle->color = false;
                grandparent->color = true;

                node = grandparent;
            }
            else {

                //LR case
                if (node == parent->right) {
                    node = parent;
                    rotateLeft(node);
                }

                //LL case
                node->parent->color = false;
                node->parent->parent->color = true;
                rotateRight(node->parent->parent);
            }
        }
        //case if parent is the right child
        else {

            Node *uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == true) {

                parent->color = false;
                uncle->color = false;
                grandparent->color = true;
                node = grandparent;
            }
            else {

                //RL case
                if (node == parent->left) {
                    node = parent;
                    rotateRight(node);
                }

                //RR case
                node->parent->color = false;
                node->parent->parent->color = true;
                rotateLeft(node->parent->parent);
            }
        }
    }

    //root stays black
    root->color = false;
}
//Check if a user exists
bool RedBlackTree::containsUser(const string &username){
    Node* curr = root;
    while(curr != nullptr){
        if(curr->username == username){
            return true;
        }
        else if(username < curr->username){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    return false;
}
//For testing and printing out tree
void RedBlackTree::printTree(Node *root){
    
    if(root!= nullptr){
        cout << root->username << " " << 
        (root->color ? "RED" : "BLACK") << endl;
        

        printTree(root->left);
        printTree(root->right);
    }
}

//destructor
RedBlackTree::~RedBlackTree() {

    vector<Node*> nodes;

    if (root != nullptr) {
        nodes.push_back(root);
    }

    //DFS to delete all nodes
    while (!nodes.empty()) {
        Node* current = nodes.back();
        nodes.pop_back();

        if (current->left != nullptr) {
            nodes.push_back(current->left);
        }

        if (current->right != nullptr) {
            nodes.push_back(current->right);
        }

        delete current;
    }
    root = nullptr;
}

