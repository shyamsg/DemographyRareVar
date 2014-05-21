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

#include "siteStat.h"
#include "argHelper.h"
#include "ARG.h"
#include <vector>

class argStatMiner {
  ARG * localARG; /**< The local copy of the ARG - still the full ARG.*/
  argHelper helper; /**< Helper class for the ARG. */

 public:
  vector<siteStat *> statVector; /**< Each site has x number of stat structures where x 
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
  void getStatsByDAC(int maxDerivedCount);

  /**
     This function obtains the stats such as core haplotype length, the length
     of second recombination and the counts of coalescing subtree for the lines
     with derived states at a given site. 
  */
  void getStatsForSite(set<int> chosenLabels, uint treeIndex);
  
  /**
     Destructor. Empty the stats matrix. 
  */
  ~argStatMiner();

};
