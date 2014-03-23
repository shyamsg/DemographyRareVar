/**
Newick Tree Node Class
=====================

This class codes the newick trees that are output by the macs. 
The tree contains the relationships between the different haplotypes;
it _also_ contains the length of the sequence for which this is the
tree. Couple of notes about the tree: firstly, the branchLen 
variable is the length of the branch that leads to the node. The 
length of the sequence that this tree is valid for is stored in the
arg. The root has a branchLen of 0. The minLeafNode of the node is
the minimum leaf label of the tree attached to this node. 

Members of the class:
---------------------
### Attributes:###
- leftSubTree
- rightSubTree
- parent
- minLeafNode

### Methods:###
- constructors
- switchChildren
- isLeaf
- isRoot
- destructor
*/

class newickTreeNode {
public:
  newickTreeNode * leftSubTree; /**< Left sub-tree.*/
  newickTreeNode * rightSubTree; /**< Right sub-tree.*/
  newickTreeNode * parent; /**< Parent node.*/
  int minLeafNode; /**< Minimum leaf node. */
  int branchLen; /**< Branch length*/
  
  /**
     A constructor. Sets all pointers to NULL, branchLen to zero
     and minLeafNode to -1. 
   */
  newickTreeNode();

  /**
     A constructor. Sets the parent to given pointer, branchLen to 
     branchLen.
   */
  newickTreeNode(int branchLen, newickTreeNode * parent);

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
  
}
