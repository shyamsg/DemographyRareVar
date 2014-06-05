/**
   ARG Statistics Miner
   ====================

   This class encodes the functions that will parse the ARG to 
   compute the statistics that are needed to be computed from 
   the ARG. 

   Members of the class:
   ---------------------
   ### Attributes:###
   - statVector
   - localARG

   ### Members:###
   - constructor
   - getStatsByDAC
   - getStatsForSite
   - destructor

*/

#ifndef __ARGSTATMINER_H__
#define __ARGSTATMINER_H__

#include "siteStat.h"
#include "argHelper.h"
#include "ARG.h"
#include <vector>

typedef unsigned int uint;

class argStatMiner {
  ARG * localARG; /**< The local copy of the ARG - still the full ARG.*/
  argHelper helper; /**< Helper class for the ARG. */

  /**
     Get the statistics for this site going right/left from the core tree. 
  */
  void getStatsDirection(set<int> chosenLabels, uint treeIndex, vector<siteStat> & stats, bool left);

  /**
     This function obtains the stats such as core haplotype length, the length
     of second recombination and the counts of coalescing subtree for the lines
     with derived states at a given site. 
  */
  void getStatsForSite(set<int> chosenLabels, uint treeIndex, int leftOnTree, int rightOnTree, pair<int, int> curDACs, float age);

  /**
    Get population counts on tree
  */
  int pop1OnTree(set<int> leaves, int pivot);

  /**
     Is the recombination taking the lineages off core?
   */
  bool isOffCore(set<int> leaves, set<int> core, float recombTime, float mutTime);

 public:
  vector<vector<siteStat> > statVector; /**< Each site has x number of stat structures where x 
				    is number of derived alleles.*/
  
  /**
     Constructor. Nothing to do.
  */
  argStatMiner();

  /**
     Constructor. Initializes the ARG.
  */
  argStatMiner(ARG *topARG);

  /**
     This function obtains the stats for all sites with less than certain derived
     allele count (DAC). It calls the getStatsForSite function for each site making
     sure that these sites get stored under the appropriate DAC. 
  */
  void getStatsByDAC(int maxDerivedCount, ofstream & outfile);

  /**
     Print the statistics computed from the ARG to a file.
  */
  void printStats(ofstream & output);

  /**
     Destructor. Empty the stats matrix. 
  */
  ~argStatMiner();

};

#endif
