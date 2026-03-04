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

  Node* head = nullptr;

  BST() { /*cout << "Head: " << head << endl; */}
  //BST(BST* i) { this->insert(i); }

  //RECURSIVE DELETE
  ~BST() { delete head; }

  //Min, succ, and search ripped off from wikipedia
  Node* min(Node* v) {

    while (v->left != nullptr) { v = v->left; }
    return v;
  }
  
  Node* succ(Node* v) {

    v = v->right;

    while (v->left != nullptr) { v = v->left; }

    return v;
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

    Node* z = new Node(v);
    Node* y = nullptr;
    Node* x = this->head;

    while (x != nullptr) {

      y = x;
      if (v < x->data) { x = x->left; }
      else { x = x->right; }
    }

    z->parent = y;

    if (y == nullptr) { head = z; }
    else if (v < y->data) { y->left = z; }
    else { y->right = z; }
  }

  void remove(int v) {

    Node* del = this->search(v);

    //Leaf
    if (del->left == nullptr and del->right == nullptr) {

      if (del->parent != nullptr) {
	
	if (del->parent->left == del) { del->parent->left = nullptr; }
	else { del->parent->right = nullptr; }
      }

      if (del == head) { head = nullptr; }
      delete del;
    }
    //One child root
    else if (del->right == nullptr or del->left == nullptr and del->parent == nullptr) {

      //Left
      if (del->right == nullptr) {

	head = del->left;
	del->left = nullptr;
	delete del;
      }
      //Right
      else {

	head = del->right;
	del->right = nullptr;
	delete del;
      }
    }
    //One child (left)
    else if (del->right == nullptr) {
	
      //Fix parent
      del->left->parent = del->parent;
	
      //del is left child
      if (del->parent->left == del) { del->parent->left = del->left; }
      //del is right child
      else { del->parent->right = del->left; }
	
      //Cleanup
      del->left = nullptr;
      delete del;
    }
    //One child (right)
    else if (del->left == nullptr) {

      //Same as left (just, right)

      del->right->parent = del->parent;

      if (del->parent->left == del) { del->parent->left = del->right; }
      else  { del->parent->right = del->right; }

      del->right = nullptr;
      delete del;
    }
    //Two children root
    else if (del == head) {

      Node* succ = this->succ(del);

      //Succ is right child
      if (succ == del->right) {

	succ->left = del->left;
	succ->parent = nullptr;
      }

      //Succ in del's subtree
      else {

	//No child succ
	if (succ->left == nullptr and succ->right == nullptr) {

	  //Fix succ's old parent
	  if (succ->parent->left == succ) { succ->parent->left = nullptr; }
	  else { succ->parent->right == nullptr; }
	}

	//One child succ
	else {

	  //Fix succ's old parent
	  if (succ->parent->left == succ) {

	    succ->parent->left = succ->right;
	    succ->right->parent = succ->parent;
	  }
	  else {

	    succ->parent->right = succ->right;
	    succ->right->parent = succ->parent;
	  }
	}
      }
	//Cleanup
	succ->left = del->left;
	succ->left->parent = succ;
	succ->right = del->right;
	succ->right->parent = succ;
        del->left = nullptr;
	del->right = nullptr;
	delete del;
    }
    //Two children
    else {

      Node* succ = this->succ(del);
      
      //Succ is right child
      if (succ == del->right) {

	succ->left = del->left;
	succ->parent = del->parent;
	if (del->parent->left == del) { succ->parent->left = succ; }
	else { succ->parent->right == succ; }
      }

      //Succ is in del's subtree
      else {

	//Fix del's parent's child
	if (del->parent->left == del) { del->parent->left = succ; }
	else { del->parent->right = succ; }

	//No child succ
	if (succ->left == nullptr and succ->right == nullptr) {

	  //Fix succ's old parent
	  if (succ->parent->left == succ) { succ->parent->left = nullptr; }
	  else { succ->parent->right = nullptr; }
	}
	
	//One child succ
	else {

	  //Fix succ's old parent
	  if (succ->parent->left == succ) {

	    succ->parent->left = succ->right;
	    succ->right->parent = succ->parent;
	  }
	  else {

	    succ->parent->right = succ->right;
	    succ->right->parent = succ->parent;
	  }
	}
  
	//Cleanup
	succ->left = del->left;
	succ->left->parent = succ;
	succ->right = del->right;
	succ->right->parent = succ;
	succ->parent = del->parent;
	del->left = nullptr;
	del->right = nullptr;
	delete del;
      }
    }
  }

  void print(int indent = 0, Node* i = nullptr) {

    if (i == nullptr) { i = head; }
    
    if (i->right != nullptr) { this->print(indent + 1, i->right); }

    for (int j = 0; j < indent; j++) { cout << "\t"; }

    if (i->parent != nullptr) {

      cout << "(";
      if (i->parent->data < 100) { cout << "0"; }
      if (i->parent->data < 10) { cout << "00"; }
      cout << i->parent->data;
      cout << ")";
    }
    if (i->data < 100) { cout << "0"; }
    else if (i->data < 10) { cout << "00"; }
    cout << i->data << endl;

    if (i->left != nullptr) { this->print(indent + 1, i->left); }
  }
};

#endif
