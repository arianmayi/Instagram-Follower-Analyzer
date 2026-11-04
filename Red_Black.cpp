//
// Created by arian on 10/15/2026.
//
#include <iostream>
#include "Red_Black.h"
using namespace std;

//DO NOT DELETE UNTIL NEAR END OF PROJECT - USE AS GUIDE

/*
 *Vitor's part
 *Red-Black implantation, where the data will be stored
 *
 *
 */
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
    //Hold node in temporary varible
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
    //Fix the tree after insertion
   
    while(node != root && node->parent != nullptr && node->parent->color == true){
        //Declare needed nodes.
        Node *parent = node->parent;
        Node *grandparent = node->parent->parent;

        if(grandparent == nullptr){
            break;
        }
        //Declara uncle to decide what case it is

        Node *uncle;

        if(parent == grandparent->left){
            uncle = grandparent->right;
        }
        else {
            uncle = grandparent->left;
        }
        //Color Change
        if(uncle != nullptr && uncle->color == true){
            //Uncle red
            parent->color = false;
            uncle->color = false;
            grandparent->color = true;

            node = grandparent;
        }
        else{
            //Parent is in the left
            if(parent == grandparent->left){
                //LR
                if(node == parent->right){
                    rotateLeft(parent);
                    //Always update parent
                    parent = node;
                }
            
            //LL
            parent->color = false;
            grandparent->color = true;
            rotateRight(grandparent);
        }
        else{
                //RL
                if(node == parent->left){
                    rotateRight(parent);
                    parent = node;
                }
                //RR
                parent->color = false;
                grandparent->color = true;

                rotateLeft(grandparent);
            }
        }
    }
    //Root is always black
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

