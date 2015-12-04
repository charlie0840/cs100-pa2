#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

template<typename Data>
class BSTNode {

public:


  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  int priority;
  Data const data;   // the const Data in this node.

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d) : data(d) {
    left = right = parent = 0;
  }

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ // TODO
  BSTNode<Data>* successor() {
    // Algorithm: Go right, and then left as far as possible.  If there
    // is no right, then go up.  If the node is a left child, that's it.
    // If the node is a right child, keep going up.  When you can't go up
    // any more you're done.
    BSTNode<Data>* current = this;
    if ( current->right != 0 ) {
      current = current->right;
      while (current->left != 0) {
	current = current -> left;
      }
      return current;
    }
    while ( current->parent != 0 ) {
      BSTNode<Data>* par = current->parent;
      if ( par->left == current ) {
	return par;
      }
      else {
	current = par;
      }
    }

    return 0;    

  }

}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
