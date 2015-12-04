/**************************************************************************
							Yiming Yu
							cs100feu

							Xiaoju Guo
							xig061
			
							CSE100 FA2015
				Assignemnt 2
File Name:	RST.cpp
Description:  	The rst.hpp file will be used to maintain the random search 
		tree structure and functionality. Subclass the BST class 
		template of the previous assignment to define a class 
		template named RST, which implements a randomized search 
		tree.	
**************************************************************************/
#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <iostream>
using std::cout;
using std::endl;
using namespace std;

template <typename Data>
class RST : public BST<Data> {

public:

  /* Insert new data into the RST if it is not already present.
   * Input
   *    item - the data to insert.
   *    return - true if the item was inserted. 
   *    	 If the item was already contained in the tree then 
   *    	 return false.
   */
  virtual bool insert(const Data& item) {
	BSTNode<Data> * curr;	//pointer to node being processed
	BSTNode<Data> * par;	//pointer to parent of node being processed
	bool right = false;
	//if there is nothing inside the tree
	if(this->empty())
	{
		//set the root to new node
		this->root = new BSTNode<Data>(item);
		this->root->priority=rand();
		return true;
	}
	else
	{
      		BSTNode<Data>* current = this->root;
     		BSTNode<Data>* last = 0;
		//while it is not the leaf
      		while ( current != 0 ) 
		{
			//go to left
			if ( item < current->data ) 
			{
	  			last = current;
	  			current = current->left;
			}
			//go to right
			else if ( current->data < item ) 
			{
	  			last = current;
	  			current = current->right;
				right = true;
			}
			else 
			{  // already in the tree
	  			return false;
			}
      		}
		//construct the new node to be inserted
      		BSTNode<Data>* newNode = new BSTNode<Data>(item);
      		if ( right == false ) 
		{
			last->left = newNode;
			newNode->parent = last;
      		}
      		else 
		{
			last->right = newNode;
			newNode->parent = last;
      		}
		//assign the new node with a priority
		newNode->priority=rand();
		curr=newNode;
		par = curr->parent;
	
    	}
		
	//start to rotate to keep the priority of nodes in order
	while(true)
	{
		//if already in order
		if(curr->priority <= par->priority)
		{	
			break;
		}
		else if(curr->priority > par->priority)
		{
			if(par->right == curr)
				rotateLeft(par,curr);
			else
				rotateRight(par,curr);
			if(curr->parent!=NULL)
				par=curr->parent;
			else
				break;
		}
	}
   	return true;
  }

private:

  /* Perform a 'right rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in
   * the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' 
   * pointers of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a left child
   *    child - the left child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but 
   *   switched in level, meaning 'par' will effectively become the 
   *   right-child of 'child'.
   *
   */
  void rotateRight( BSTNode<Data>* par, BSTNode<Data>* child ) {
	//if par is not the root
	if(par->parent!=NULL)
	{
		if(par->parent->left==par)
			par->parent->left=child;
		else
		{
			par->parent->right=child;
		}


	}
	else	//set the root to child
		BST<Data>::root=child;
	child->parent=par->parent;
	par->parent=child;		
	
	if(child->right==NULL)
	{
		child->right=par;
		par->left=NULL;
	}
	else
	{
		par->left=child->right;
		child->right->parent=par;
		child->right=par;
	}
  }


  /* Perform a 'left rotation' that changes the structure of the tree 
   * without interfering with the size, data content, and left->right 
   * order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 
   * 'parent' pointers of a subset of nodes without changing 
   * their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a right child
   *    child - the right child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order 
   *   but switched in level, meaning 'par' will effectively become the 
   *   left-child of 'child'.
   *
   */
  void rotateLeft( BSTNode<Data>* par, BSTNode<Data>* child )
  {

    	//if par is not root
	if(par->parent!=NULL)
	{
		if(par->parent->left==par)
			par->parent->left=child;
		else
			par->parent->right=child;


	}
	else	//set the root to child
		BST<Data>::root=child;
		
	child->parent=par->parent;
	par->parent=child;
	
	if(child->left==NULL)
	{
		child->left=par;
		par->right=NULL;
	}
	else
	{
		par->right=child->left;
		child->left->parent=par;
		child->left=par;
	}

  }

public:

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   *
   * Calls BST::insert so we can add data to test rotateRight and rotateLeft before
   * implementing the fully correct version of RST::insert.
   *
   */
  bool BSTinsert(const Data& item) {

    return BST<Data>::insert(item);

  }

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   *
   * Locates the node for an item and rotates it left or right without changing the
   * left->right order of nodes in the RST
   * Input
   *    item - the Data item to rotate.
   *    leftOrRight - if true then rotateLeft, otherwise rotateRight
   *    output - 0 if item could be found and had a child to rotate with, 1 if not. -1 if
   *         rotation failed for other reasons
   */
  int findAndRotate(const Data& item, bool leftOrRight) {

     BSTNode<Data>* current = RST<Data>::root;
     while ( current != 0 ) {
       if ( item < current->data ) {
         current = current->left;
       }
       else if ( current->data < item ) {
         current = current->right;
       }
       else {  // already in the tree
         break;
       }
     }

     if (current == 0 or current->data != item) {
       return 1;
     }

     if (leftOrRight) {
       if (current->right == 0) {
         return 1;
       }
       BSTNode<Data>* right = current->right;
       rotateLeft(current, current->right);

       // make sure we actually do a rotation
       if (current->right == right) {
         return -1;
       }

     } else {
       if (current->left == 0) {
         return 1;
       }
       BSTNode<Data>* left = current->left;
       rotateRight(current, current->left);

       // make sure we actually do a rotation
       if (current->left == left) {
         return -1;
       }
     }
     return 0;
  }
};
#endif // RST_HPP
