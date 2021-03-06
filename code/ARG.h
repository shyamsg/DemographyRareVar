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
   - recombList
   - polymorphisms
   - variantPos
   - mutTimes
   - recombFromTimes
   - recombToTimes
   - regionLength
   
   ### Methods:###
   - constructors
   - parseMACSOutput
   - getVariants
   - getTree
   - destructor
   
*/


#ifndef __ARG_H__
#define __ARG_H__

#include "newickTreeNode.h"
#include <vector>
#include <string>

using namespace std;

class ARG {
  /**
     Helper attributes for tokenizing to parse tree.
   */
  const static char sqClose = ']';
  const static char sqOpen = '[';

  /**
     Function to read variant line in MACS output and add this variant
     to the vector of variants. 
  */
  void getVariants(string & line);
  
  /**
     Function to read the tree line in MACS output and add the tree to the
     list of trees.
  */
  void getTree(string & line);

  /**
     Function to convert string to bit vector.
   */
  vector<bool> makeBitVector(string token);

  /**
     Populate recombList by parsing across the list of trees in the ARG.
  */
  void populateRecombList();

 public:
  vector<newickTreeNode *> treeList; /**< List of trees that make up the ARG*/
  vector<int> treeSeqLengths; /**< Vector containing the lengths of the sequences for each tree*/
  vector<set<int> > recombList; /**< List of lines that recombined from tree t to t+1*/
  vector<set<int> > recombedFromList;
  vector<set<int> > recombedToList;
  vector<float> recombFromTimes;
  vector<float> recombToTimes;
  vector<vector<bool> > polymorphisms; /**< Matrix of polymorphisms - stored as 0/1 */
  vector<int> variantPos; /**< Position of SNPs */
  vector<float> mutTimes; /**< Times of mutations, in 2N generation units */
  int regionLength; /**< Length of simulated region */
  int pop1Size; /**< Number of samples in population 1 */

  /**
     Constructor - does nothing :) 
  */
  ARG() {};
  
  /**
     Function to parse the MACS output and populate the attributes of the class.
     Generates the trees from the output and stores the polymorphisms for processing.
  */
  void parseMACSOutput(const char * macsFileName);
  
  /**
     Destructor - delete all the trees and empty the vectors.
  */
  ~ARG();  
};

#endif
