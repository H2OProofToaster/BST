#ifndef STRUCTS_CPP
#define STRUCTS_CPP

struct Node {

  int data;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;

  Node() {}
  Node(d) : data(d) {}

  ~Node() { delete left; delete right; }
};

struct BST {

  Node* head;

  BST() {}
  //BST(BST* i) { this->insert(i); }

  //RECURSIVE DELETE
  ~BST() { delete head; }

  Node* search(int v) {

    Node* t = head;
    while (t != nullptr and t->data != v) {

      if (v < t->data) { t = t->left; }
      else { t = t->right; }
    }
    return t;
  }
  
  void insert(int v) {

    return
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
    else if (del->left == nullptr ^ del->right == nullptr) {

      
    
};

#endif
