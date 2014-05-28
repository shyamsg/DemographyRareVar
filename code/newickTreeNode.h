/**
   Newick Tree Node Class
   ======================
   
   This class codes the newick trees that are output by the macs. 
   The tree contains the relationships between the different haplotypes;
   it _also_ contains the length of the sequence for which this is the
   tree. Couple of notes about the tree: firstly, the branchLen 
   variable is the length of the branch that leads to the node. The 
   length of the sequence that this tree is valid for is stored in the
   arg. The root has a branchLen of 0. The minLeafNode of the node is
   the minimum leaf label of the tree attached to this node - so the
   minimum of the leafList.
   
   Members of the class:
   ---------------------
   ### Attributes:###
   - leftSubTree
   - rightSubTree
   - parent
   - leafList
   - branchLen
   
   ### Methods:###
   - leafDifference
   - constructors
   - switchChildren
   - isLeaf
   - isRoot
   - minLeafNode
   - findLeaf
   - isCommonAncestor
   - findMRCANode
   - getRecombined
   - getRecombinedAdjoint
   - destructor
*/

#ifndef __NEWICKTREENODE_H__
#define __NEWICKTREENODE_H__

#include <set>
#include <utility>
#include <vector>

using namespace std;

typedef pair<float, set<int> > pairstat;

class newickTreeNode {  
  
  /**
     Obtain the leaf difference based on whether the left trees
     have fewer, more or different leaves. Used by the getRecombined
     method.
  */
  set<int> leafSymmetricDifference(set<int> otherLeaves);

 public:
  newickTreeNode * leftSubTree; /**< Left sub-tree.*/
  newickTreeNode * rightSubTree; /**< Right sub-tree.*/
  newickTreeNode * parent; /**< Parent node.*/
  set<int> leafList; /**< List of leaves under this node */
  float branchLen; /**< Branch length*/
  
  /**
     A constructor. Sets all pointers to NULL, branchLen to zero
     and leafList to empty set. 
  */
  newickTreeNode();
  
  /**
     A constructor. Sets the parent to given pointer, branchLen to 
     branchLen.
  */
  newickTreeNode(float branchLen, newickTreeNode * parent);
  
  /**
     A destructor. Clears all pointers, before that
     it calls the destructor of the right and left
     sub-trees.
  */
  ~newickTreeNode();
  
  /**
     Is this node a root node? Returns a boolean.
  */
  bool isRoot();
  
  /**
     Is this node a leaf node? Returns a boolean.
  */
  bool isLeaf();
  
  /**
     This switches the left and right child nodes. 
     The minLeafNode of the left tree must be less
     than the minLeafNode of the right tree. This 
     property is used to make sure that we can 
     compare 2 trees easily. 
  */
  void switchNodes();
  
  /**
     Comparison operator to compare two newick trees.
  */
  bool operator== (const newickTreeNode & other) const;
  
  /**
     Return pointer to leaf node with chosen label.
  */
  newickTreeNode * findLeaf(int leafNodeName);
  
  /**
     Return the minimum leaf node attached to this node.
  */
  int minLeafNode();
  
  /**
     Prints newick trees using the bracket representation.
  */
  void printTree();
  
  /**
     Is this node a common ancestor to the given set of nodes.
  */
  bool isCommonAncestor(const set<int> givenNodes);

  /**
     Finds the node which is the MRCA of the given set of nodes.
  */
  newickTreeNode * findMRCANode(const set<int> givenNodes);

  /**
     Get the set of recombined lines between this and the passed tree.
     Assumes that there is at most one recombination event for now. Should
     be easy to extend to multiple recombination events - here it looks
     for exactly one set of lines which recombined. In the multiple case,
     it is a union of all the sets. 
  */
  set<int> getRecombined(newickTreeNode * other);
  
  /**
     Get the subtree to which this set of leaves recombined with. The implicit 
     assumption is that the set of leaves here forms a complete subtree => 
     the MRCA node of these leaves has exactly these leaves in its leaf list. 
     In a donor tree, the leaves are the subtree that these leaves recombined 
     from. In a receiver tree, these are the leaves of the subtree that were 
     recombined onto. 
  */
  set<int> getRecombinedAdjoint(const set<int> leaves);

};

#endif
