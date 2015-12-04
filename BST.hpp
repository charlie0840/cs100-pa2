#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    deleteAll(root);
  }


  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items.
   */ 
  virtual bool insert(const Data& item) {
    if (empty()) {
      root = new BSTNode<Data>(item);
      return true;
    }
    else {
      BSTNode<Data>* current = root;
      BSTNode<Data>* last = 0;
      while ( current != 0 ) {
	if ( item < current->data ) {
	  last = current;
	  current = current->left;
	}
	else if ( current->data < item ) {
	  last = current;
	  current = current->right;
	}
	else {  // already in the tree
	  return false;
	}
      }
      BSTNode<Data>* newNode = new BSTNode<Data>(item);
      if ( item < last->data ) {
	last->left = newNode;
	newNode->parent = last;
      }
      else {
	last->right = newNode;
	newNode->parent = last;
      }
      return true;
	
    }
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items.
   */ 
  iterator find(const Data& item) const {

    BSTNode<Data>* current = root;
    while ( current != 0 ) {
      if ( item < current->data ) {
	current = current->left;
      }
      else if ( current->data < item ) {
	current = current->right;
      }
      else {  // already in the tree
	return iterator(current);
      }
    }
    return end();
  }

  
  /** Return the number of items currently in the BST.
   */
  unsigned int size() const {
    return sizeHelp(root);
  }

  /** Return true if the BST is empty, else false.
   */
  bool empty() const {
    return root == 0;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ 
  iterator begin() const {
    return typename BST<Data>::iterator(first(root));
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Helper function to find the size */
  int sizeHelp( BSTNode<Data>* curr ) const {
    if (curr == 0) {
      return 0;
    }
    else {
      return 1 + sizeHelp(curr->left) + sizeHelp(curr->right);
    }
  }

  /** Recursive inorder traversal 'helper' function */
  void inorder(BSTNode<Data>* n) const {
    if(n==0) return;
    inorder(n->left);
    std::cout << *n << std::endl;
    inorder(n->right);
  }

  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  // do a postorder traversal, deleting nodes
  static void deleteAll(BSTNode<Data>* n) {
    if (0 == n) return;
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;
  }


 };


#endif //BST_HPP
