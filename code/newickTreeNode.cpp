#include "newickTreeNode.h"
#include <algorithm>
#include <iostream>
#include <iterator>

newickTreeNode::newickTreeNode() {
  // Set all the pointers to NULL
  this->leftSubTree = NULL;
  this->rightSubTree = NULL;
  this->parent = NULL;

  // Set the other attributes to defaults
  this->branchLen = 0;
}

newickTreeNode::newickTreeNode(float branchLen, newickTreeNode * parent) {
  // Set the child nodes to NULL and leaf node to default
  this->leftSubTree = NULL;
  this->rightSubTree = NULL;

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
  return (this->parent == NULL);
}

bool newickTreeNode::isLeaf() {
  return (leftSubTree==NULL && rightSubTree == NULL);
}

void newickTreeNode::switchNodes() {
  //Test to see if it has right child
  if (rightSubTree == NULL) return;
  // if no left child and right child present, then switch them
  if (leftSubTree == NULL) {
    leftSubTree = rightSubTree;
    rightSubTree = NULL;
    return;
  }
  // if left's min leaf is less than right's min leaf switch them.
  if (leftSubTree->minLeafNode() > rightSubTree->minLeafNode()) {
    newickTreeNode * temp = leftSubTree;
    leftSubTree = rightSubTree;
    rightSubTree = temp;
  }
}

bool newickTreeNode::operator== (const newickTreeNode & other) const {
  //Check that the trees under the node are the same.
  if (this->branchLen != other.branchLen)
    return false;
  if (this-> leafList != other.leafList)
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

set<int> newickTreeNode::leafSymmetricDifference(set<int> otherLeaves) {
  set<int> leafDiff;
  set<int>::iterator sit;
  set<int>::iterator sit2;
  for (sit = this->leafList.begin(); sit != this->leafList.end(); sit++) {
    sit2 = otherLeaves.find(*sit);
    if ( sit2 == otherLeaves.end()) {
      leafDiff.insert(*sit);
    } else {
      otherLeaves.erase(sit2);
    }
  }
  for (sit = otherLeaves.begin(); sit != otherLeaves.end(); sit++) {
    if (this->leafList.find(*sit) == this->leafList.end()) {
      leafDiff.insert(*sit);
    }
  }
  return leafDiff;
}

set<int> newickTreeNode::getRecombined (newickTreeNode * other) {
  // Find the lines that recombined from this tree to the next
  // Assumes that there is only one recombination for now.
  // Go left and extract that left subtree's recombination, if that is 
  // empty, the go right and extract that tree's recombination. If both are 
  // empty, then something is wrong and the trees are the same -> not possible
  // since exactly one recombination between the neighboring trees :)

  set<int> temp; // return variable with labels of the recombined nodes.
  // At root or an internal node in both trees
  if (this->leftSubTree != NULL && this->rightSubTree != NULL &&
    other->leftSubTree != NULL && other->rightSubTree != NULL) {
    // nodes have switched from left to right subtree or vice versa
    if (this->leftSubTree->leafList != other->leftSubTree->leafList) {
      // compute the difference in the leaf list and this is the set of lines
      // that has recombined
      unsigned int sizediff = (unsigned int) abs((int) this->leftSubTree->leafList.size() - 
						 (int) other->leftSubTree->leafList.size());
      // If the subtree containing 0 label switches from left to right then the root of this
      // tree is going to get rearranged - switch of left and right nodes - check for that 
      temp = this->leftSubTree->leafSymmetricDifference(other->leftSubTree->leafList);
      if (temp.size() != sizediff) {
	temp = this->leftSubTree->leafSymmetricDifference(other->rightSubTree->leafList);
      }
      return temp;
    }
    // the length of the left subtree branches are different - leaf lists
    // are not, so invisible recombination, assign the subtree as recombined
    // proportional to its branch length
    if (this->leftSubTree->branchLen != other->leftSubTree->branchLen) {
      if (isRoot()) { // the root moved back
	float leftProp = this->leftSubTree->branchLen;
	leftProp = leftProp/(leftProp+this->rightSubTree->branchLen);
	if (drand48() < leftProp)
	  temp = this->leftSubTree->leafList;
	else
	  temp = this->rightSubTree->leafList;
      } else {
	float leftProp = this->leftSubTree->leftSubTree->branchLen;
	leftProp = leftProp/(leftProp+this->leftSubTree->rightSubTree->branchLen);
	if (drand48() < leftProp)
	  temp = this->leftSubTree->leftSubTree->leafList;
	else
	  temp = this->leftSubTree->rightSubTree->leafList;
      }
      return temp;
    }
    // the length of the right subtree branches are different - leaf lists
    // are not, so invisible recombination, assign the subtree as recombined
    // proportional to its branch length
    if (this->rightSubTree->branchLen != other->rightSubTree->branchLen) {
      float leftProp = this->rightSubTree->leftSubTree->branchLen;
      leftProp = leftProp/(leftProp+this->rightSubTree->rightSubTree->branchLen);
      if (drand48() < leftProp)
	temp = this->rightSubTree->leftSubTree->leafList;
      else
	temp = this->rightSubTree->rightSubTree->leafList;
      return temp;      
    }
    // This is not the tree minimal tree of recombination - look at the left and right 
    // children one by one. Left first, then right.
    temp = this->leftSubTree->getRecombined(other->leftSubTree);
    if (!temp.empty()) return temp;
    temp = this->rightSubTree->getRecombined(other->rightSubTree);
    if (!temp.empty()) return temp;
  } 
  // This is a leaf node in at least one of the trees - return an empty set
  return temp;
}

set<int> newickTreeNode::getRecombinedAdjoint(const set<int> leaves) {
  // Find the MRCA node of these leaves
  if (leaves.empty()) {
    set<int> emptyset;
    return emptyset;
  }
  newickTreeNode * temp = this->findMRCANode(leaves);
  if (temp->isRoot()) {
    cerr << "These leaves have root as their MRCA. Are you sure that is correct?" << endl;
    exit(3);
  }
  // return sister subtree's leaf list
  if (temp == temp->parent->leftSubTree)
    return temp->parent->rightSubTree->leafList;
  return temp->parent->leftSubTree->leafList;
}

newickTreeNode * newickTreeNode::findLeaf(int leafNodeName) {
    if (this->isLeaf()) {
      if (this->minLeafNode() == leafNodeName)
	return this;
      else
	return NULL;
    } else {
      newickTreeNode * leftNewickTree = leftSubTree->findLeaf(leafNodeName);
      if (leftNewickTree != NULL) {
	return leftNewickTree;
      }
      newickTreeNode * rightNewickTree = rightSubTree->findLeaf(leafNodeName);
      if (rightNewickTree != NULL) {
	return rightNewickTree;
      }
    }
    return NULL;
}

int newickTreeNode::minLeafNode(){
  if (leafList.empty()) return -1;
  return *(leafList.begin());
}

void newickTreeNode::printTree() {
  if (!this->isLeaf()) cout << "(";
  if (this->isLeaf()) {
    cout << minLeafNode(); 
  } else {
    if (leftSubTree != NULL)
      leftSubTree->printTree();
    cout <<",";
    if (rightSubTree != NULL)
      rightSubTree->printTree();
  }
  if (!this->isLeaf()) cout << ")";
  if (this->isRoot()) {
    cout << endl;
  } else {
    cout << ":" << branchLen;
  }
}

bool newickTreeNode::isCommonAncestor(const set<int> givenNodes) {
  //  cout << "Given: "; copy(givenNodes.begin(), givenNodes.end(), ostream_iterator<int>(cout, " ")); cout << endl;
  //  cout << "Leaflist: "; copy(leafList.begin(), leafList.end(), ostream_iterator<int>(cout, " ")); cout << endl;
  for (set<int>::iterator iit = givenNodes.begin(); iit != givenNodes.end(); iit++) {
    //    cout << " _ " << *iit << " _ " << endl;
    if (leafList.find(*iit) == leafList.end())
      return false;
  }
  return true;
}

newickTreeNode * newickTreeNode::findMRCANode(const set<int> givenNodes) {
  if (this->isRoot())
    if (!(this->isCommonAncestor(givenNodes)))
      return NULL;
  if (this->isLeaf())
    return (this->isCommonAncestor(givenNodes) ? this : NULL);
  else if (this->leftSubTree->isCommonAncestor(givenNodes))
    return leftSubTree->findMRCANode(givenNodes);
  else if (this->rightSubTree->isCommonAncestor(givenNodes))
    return rightSubTree->findMRCANode(givenNodes);
  else
    return this;
}

float newickTreeNode::getTotalTime() {
  return (this->isLeaf() ? this->branchLen: this->branchLen+this->leftSubTree->getTotalTime()); 
}

// Obsolete function to get the lineage of a leaf node - path of 
// internal nodes and times till you reach root.
/*
vector<pairstat> newickTreeNode::getLineage(int leafNodeName) {
  vector<pairstat> lineage;
  newickTreeNode * leafNode = findLeaf(leafNodeName);
  while(!leafNode->isRoot()) {
    pairstat temp;
    temp.first = leafNode->branchLen;
    set_difference(leafNode->leafList.begin(), leafNode->leafList.end(), 
		   lineage.back().second.begin(), lineage.back().second.end(),
		   inserter(temp.second, temp.second.begin()));
    lineage.push_back(temp);
    leafNode = leafNode->parent;
  }
  return lineage;
}
*/
