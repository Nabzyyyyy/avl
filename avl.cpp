// Nabil Sawan

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "AVL.hpp"

int main() {

  // srand(time(0));

  // AVLTree<int>* avl = new AVLTree<int>;
  // /*
  // for (int i = 0; i < 16; ++i)
  //   avl->insert(rand() % 100);
  // */

  // for (auto x : { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }) 
  //   avl->insert(x);

  // std::cout << avl->serialize() << std::endl;
AVL<int> avl;

  std::cout << "----------------------------------------------------" << std::endl;
  for (auto x : { 1, 2, 3, 4, 5, 6, 7 })
    avl.insert(x);
  std::cout << avl.serialize() << std::endl;
  std::cout << "----------------------------------------------------\n" << std::endl;

  avl.clear();

  std::cout << "----------------------------------------------------" << std::endl;
  std::cout<< "Before insert." << std::endl;
  for (auto x : { 30, 10, 50, 48, 20 })
    avl.insert(x);
  std::cout<< "After insert before serialize." << std::endl;
  std::cout << avl.serialize() << std::endl;
  std::cout << "----------------------------------------------------\n" << std::endl;

  avl.clear();

  std::cout << "----------------------------------------------------" << std::endl;
  for (auto x : { 1, 2, 3, 4, 5, 6, 7 })
    avl.insert(x);
  for (auto x : { 4, 3 })
    avl.remove(x);
  std::cout << avl.serialize() << std::endl;
  std::cout << "----------------------------------------------------\n" << std::endl;

  avl.clear();

  std::cout << "----------------------------------------------------" << std::endl;
  for (auto x : { 10, 5, 15, 9, 8, 7, 6 })
    avl.insert(x);
  for (auto x : { 10, 9 })
    avl.remove(x);
  for (auto x : { 30, 10, 11, 12 })
    avl.insert(x);
  std::cout << avl.serialize() << std::endl;
  std::cout << "----------------------------------------------------\n" << std::endl;

  avl.clear();
}

