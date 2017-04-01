// Nabil Sawan
// njs62@zips.uakron.edu 

#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

template <class T>
struct AVLNode {
  T data;
  int height = 0;
  AVLNode<T>* left = nullptr, * right = nullptr, * parent = nullptr;

  AVLNode(T t) : data(t) {}
  AVLNode(T t, AVLNode<T>* p) : data(t), parent(p) {}
};

template <class T>
class AVL {
public:
  AVLNode<T>* root = nullptr;

  void insert(AVLNode<T>*, T);
  void update_height(AVLNode<T>*);
  int  check_balance(AVLNode<T>*);
  void left_rotate(AVLNode<T>*);
  void right_rotate(AVLNode<T>*);
  void double_left_rotate(AVLNode<T>*);
  void double_right_rotate(AVLNode<T>*);
  void serialize(AVLNode<T>*, std::stringstream&);
  void clear();
  void clear(AVLNode<T>*);
  void remove(T);
  void rebalance(AVLNode<T>*);
  void update_tree(AVLNode<T>*);
  AVLNode<T>* search(T);
  AVLNode<T>* search(AVLNode<T>*, T);

public:
  AVL() {}
  ~AVL() {}

  void insert(T);

  std::string serialize(); // helper that calls a recursive
};

template <class T>
void AVL<T>::update_height(AVLNode<T>* n) {
  if (!n)
    return;

  n->height = 1 + std::max(n->left ? n->left->height : -1, n->right ? n->right->height : -1);
}

template <class T>
int AVL<T>::check_balance(AVLNode<T>* n) {
  return (n->left ? n->left->height : -1) - (n->right ? n->right->height : -1);
}

template <class T>
void AVL<T>::left_rotate(AVLNode<T>* n) {
  AVLNode<T>* p = n;
  AVLNode<T>* m = n->right;
  p->right = m->left;

  if (m->left)
    m->left->parent = p;

  m->parent = n->parent;

  m->left = p;
  p->parent = m;

  if (!m->parent)
    root = m;
  else
    m->data < m->parent->data ? m->parent->left = m : m->parent->right = m;

  update_height(p);
  update_height(m);
}

template <class T>
void AVL<T>::right_rotate(AVLNode<T>* n) {
  AVLNode<T>* p = n;
  AVLNode<T>* m = n->left;
  p->left = m->right;
  if (m->right)
    m->right->parent = p;

  m->parent = n->parent;

  m->right = p;
  p->parent = m;

  if (!m->parent)
    root = m;
  else
    m->data < m->parent->data ? m->parent->left = m : m->parent->right = m;

  update_height(p);
  update_height(m);
}

template <class T>
void AVL<T>::double_left_rotate(AVLNode<T>* n) {
  right_rotate(n->right);
  left_rotate(n);
}

template <class T>
void AVL<T>::double_right_rotate(AVLNode<T>* n) {
  left_rotate(n->left);
  right_rotate(n);
}

template <class T>
void AVL<T>::insert(T t) {
  if (!root) {
    root = new AVLNode<T>(t); 
    return;
  }
  insert(root, t); // recursive function call
}

template <class T>
void AVL<T>::insert(AVLNode<T>* n, T t) {
  if (n->data == t)
    return;

  if (n->data > t) {
    if (n->left) {
      insert(n->left, t);
    } 
    else {
      n->left = new AVLNode<T>(t, n);
    }
  } 
  else { 
    if (n->right) {
      insert(n->right, t);
    } 
    else {
      n->right = new AVLNode<T>(t, n);
    }
  }
  update_height(n); 
  int bf = check_balance(n);
  if (bf < -1) {
   if (check_balance(n->right) > 0) {
      double_left_rotate(n);
   }
   else {
     left_rotate(n);
   }
  }
  else if (bf > 1) {
    if (check_balance(n->left) < 0) {
      double_right_rotate(n);
    }
    else {
      right_rotate(n);
    }
  }
}
 

template <class T>
std::string AVL<T>::serialize() {
  std::stringstream ret;
  serialize(root, ret);
  return ret.str();
}

template <class T>
void AVL<T>::serialize(AVLNode<T>* n, std::stringstream& s) {
  //std::cout << "Beginning of serialize" << std::endl;
  if (!n) {
    s << "/ ";
    return;
  }

  s << "[" << n->data << "|" << n->height << "] ";
  serialize(n->left, s);
  serialize(n->right, s);
}

template <class T>
void AVL<T>::clear() {
  if (root != nullptr) {
    clear(root);
  }
  else 
    return;
}

template <class T>
void AVL<T>::clear(AVLNode<T>* n) {
  if (n != nullptr) {
  //std::cout << "Are we clearing? ";

  if (n == root) {
    root = nullptr;
    return;
  }
  if (n->left)
    clear(n->left);
  if (n->right)
    clear(n->right);

  delete n;
  return;
  }
} 


template <class T>
void AVL<T>::remove(T t) {
  // find the node we'd like to remove
  AVLNode<T>* n = search(t);
  AVLNode<T>* parent;

  // return if node not in tree
  if (n == nullptr) {
    return;
  }


  // if node to delete has no children (left child == null and right child == null)
  if (n->left == nullptr && n->right == nullptr) {
     parent = n->parent; // parent = t->parent
      // delete pointer from parent
        if (parent->left == n) // if parent->left == t, parent->left = null
          parent->left = nullptr;
        else  // else parent-> right = null
          parent->right = nullptr;
      // update tree 
      update_tree(parent);
     return;
  }

  // if node to delete has right child

  if (n->left == nullptr) { // if t->left == null 
    parent = n->parent; // parent = t->parent
    
    if (parent->left == nullptr)// if parent->left == t 
      parent->left = n->right; // parent->left = t->right;
    else // else 
      parent->right = n->right;    // parent->right = t->right;
    //update tree
    update_tree(parent);
    return;
  }

  // if node to delete has left child

    if (n->right == nullptr) { // if t->right == null
      parent = n->parent; // parent = t->parent
      if (parent->left == n) // if parent->left == t
        parent->left = n->left; // parent->left = t->left
      else // else 
        parent->right = n->left; // parent->right = t->left
    //update tree
    update_tree(parent);
    return;
    }


  // if node to delete has two children
    if (n->right != nullptr && n->left != nullptr) {

      // find the in order predeccessor
      AVLNode<T>* iop = n->left;//predeccessor = t->left; 

      bool delParent = false;
      if (iop->right == nullptr)
        delParent = true;
      while (iop->right != nullptr)
        iop = iop->right;
      // save the iop's parent
      AVLNode<T>* parent = iop->parent;
      // assign the iop's child (if any) to it's parent 
      if (!delParent) {
      parent->right = iop->left;

      //AVLNode<T>* placeholder = n; // DO I NEED THIS
      // assign the node to replace n with n's children
      iop->left = n->left;
      iop->right = n->right;
      // now replace the node's data with iop's data
      n->data = iop->data;
      // delete the iop that replaced n
      delete iop;

      //update tree
      update_tree(parent);
      return;
      }
      else {
         n->left = iop->left;

         n->data = iop->data;
        // delete the iop that replaced n
        delete iop;
        //update tree
        update_tree(parent);
        return;
      }
  }
}

template <class T>
void AVL<T>::rebalance(AVLNode<T>* n) {
  int bf = check_balance(n);

  if (bf < -1) {
   if (check_balance(n->right) > 0) {
      double_left_rotate(n);
   }
   else {
     left_rotate(n);
   }
  }
  else if (bf > 1) {
    if (check_balance(n->left) < 0) {
      double_right_rotate(n);
    }
    else {
      right_rotate(n);
    }
  }

}

template <class T>
void AVL<T>::update_tree(AVLNode<T>* n) {
  // update height of parent
  update_height(n);
  rebalance(n);
  // rebalance while updating height of all parents
  while(n->parent) {
    n = n->parent;
    update_height(n);
    rebalance(n);
  }
}


template <class T>
AVLNode<T>* AVL<T>::search(AVLNode<T>* n, T t) {

  if (n->data == t)
    return n;

  else if (t < n->data)
    return search(root->left, t);

  else if(t > n->data)
    return search(root->right, t);
}

template <class T>
AVLNode<T>* AVL<T>::search(T t) {

  if(root == nullptr) {
    std::cout << "Tree is empty.";
    return nullptr;
  }

  if (root->data == t) {
    return root;
  }


  if(t < root->data)
  {
    return search(root->left, t);
  }
  else if(t > root->data)
  {
    return search(root->right, t);
  }

}
#endif
