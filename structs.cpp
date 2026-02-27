#ifndef STRUCTS_CPP
#define STRUCTS_CPP

#include <iostream>

using namespace std;

struct Node {

  int data;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;

  Node() {}
  Node(int d) : data(d) {}

  ~Node() { delete left; delete right; }
};

struct BST {

  Node* head;

  BST() {}
  //BST(BST* i) { this->insert(i); }

  //RECURSIVE DELETE
  ~BST() { delete head; }

  //Min, succ, and search ripped off from wikipedia
  Node* min(Node* v) {

    while (v->left != nullptr) { v = v->left; }
    return v;
  }
  
  Node* succ(Node* v) {

    if (v->right != nullptr) { return this->min(v->right); }

    Node* y = v->parent;
    while (y != nullptr and v == y->right) { v = y; y = y->parent; }
    return y;
  }
  
  Node* search(int v) {

    Node* t = head;
    while (t != nullptr and t->data != v) {

      if (v < t->data) { t = t->left; }
      else { t = t->right; }
    }
    
    return t;
  }
  
  void insert(int v) {

    Node* newVal = new Node(v);
    
    Node* y = nullptr;
    Node* x = head;

    while (x != nullptr) {
      y = x;

      if (newVal->data < x->data) { x = x->left; }
      else { x = x->right; }
    }

    newVal->parent = y;
    if (y == nullptr) { head = newVal; }
    else if (newVal->data < y->data) { y->left = newVal; }
    else { y->right = newVal; }
  }

  void remove(int v) {

    Node* del = this->search(v);

    //Leaf
    if (del->left == nullptr and del->right == nullptr) {

      if (del->parent->left == del) { del->parent->left = nullptr; }
      else { del->parent->right = nullptr; }

      delete del;
    }
    //One child
    else if (del->left == nullptr or del->right == nullptr) {

      Node* correctParentSide = (del->parent->left == del) ? del->parent->left : del->parent->right;
      Node* correctDelSide = (del->left == nullptr) ? del->right : del->left;
      
      //Fix new node's parent
      correctDelSide->parent = del->parent;

      //Fix parent nodes child
      correctParentSide == correctDelSide;

      //Cleanup
      correctDelSide = nullptr;
      delete del;
    }
    //Two children
    else {

      Node* succ = this->succ(del);
      
      //Succ is right child
      if (succ == del->right) {

	succ->left = del->left;
	succ->parent = del->parent;
	del->parent->left == del ? succ->parent->left : succ->parent->right = succ;
      }

      //Succ is in del's subtree
      else {

	succ->left = del->left;
	succ->right = del->right;
	succ->parent = del->parent;
	del->parent->left == del ? succ->parent->left : succ->parent->right = succ;
      }
    }
  }

  void print(int indent = 0, Node* i = nullptr) {

    if (i == nullptr) { i = head; }
    
    if (i->right != nullptr) { print(indent + 1, i->right); }

    for (int j = 0; j < indent; j++) { cout << "\t"; }

    if (i->data < 100) { cout << "0"; }
    else if (i->data < 10) { cout << "00"; }
    cout << i->data << endl;

    if (i->left != nullptr) { print(indent + 1, i->left); }
  }
};

#endif
