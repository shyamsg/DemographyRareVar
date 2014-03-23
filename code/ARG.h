/**
ARG class
=========

This class contains the whole ARG for the region. It includes 
information on the polymorphisms in the region, in the form of 
matrix of 1's and 0's. It also contains the _list of trees_ that
comprise the ARG - one tree for each piece of non-recombined 
segment.

Members of the class:
---------------------
### Attributes:###
- treeVector
- treeSeqLengths
- polymorphisms

### Methods:###
- constructors
- parseMACSOutput
- 
- destructor

*/


#include "newickTreeNode.h"
#include <vector>

class ARG {
  vector<newickTreeNode *> treeList; /**< List of trees that make up the ARG*/
  
}
