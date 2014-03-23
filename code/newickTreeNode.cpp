#include "newickTreeNode.hpp"
#include <stdlib>
#include <iostream>

newickTreeNode::newickTreeNode() {
  // Set all the pointers to NULL
  this->leftSubTree = NULL;
  this->rightSubTree = NULL;
  this->parent = NULL;

  // Set the other attributes to defaults
  this->length = 0;
  this->minLeafNode=-1;
}

newickTreeNode::newickTreeNode(int branchLen, newickTreeNode * parent) {
  // Set the child nodes to NULL and leaf node to default
  this->leftSubTree = NULL;
  this->rightSubTree = NULL;
  this->minLeafNode = -1;

  // Set the length and parent to inputs
  this->parent = parent;
  this->branchLen = branchLen;
}

newickTreeNode::~newickTreeNode() {
  // Clear the pointers and call the destructors of the children
  delete leftSubTree;
  delete rightSubTree;
}

bool newickTreeNode::isRoot() {
  return (parent == NULL);
}

bool newickTreeNode::isLeaf() {
  return (leftSubTree==NULL && rightSubTree == NULL);
}

void newickTreeNode::switchNodes() {
  if (rightSubTree == NULL) return;
  if (leftSubTree == NULL) {
    leftSubTree = rightSubTree;
    rightSubTree = NULL;
  }
  if (leftSubTree->minLeafNode > rightSubTree->minLeafNode) {
    newickTreeNode * temp = leftSubTree;
    leftSubTree = rightSubTree;
    rightSubTree = temp;
  }
}

bool newickTreeNode::operator== (const newTreeNode & other) const {
  //Check that the trees under the node are the same.
  if (this->branchLen != other.branchLen)
    return false;
  if (this-> minLeafNode != other.minLeafNode)
    return false;
  if (this->leftSubTree != NULL)
    if (this->rightSubTree != NULL)
      return ((*(this->leftSubTree) == *(other.leftSubTree)) &&
	      (*(this->rightSubTree) == *(other.rightSubTree)));
    else
      return ((*(this->leftSubTree) == *(other.leftSubTree)) &&
	      (other.rightSubTree == NULL));
  else
    if (this->rightSubTree != NULL)
      return ((other.leftSubTree == NULL) &&
	      (*(this->rightSubTree) == *(other.rightSubTree)));
    else
      return ((other.leftSubTree == NULL) && 
	      (other.rightSubTree == NULL));
  return true;
}

