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
#include <vector>

class argStatMiner {
 public:
  vector<siteStat *> statVector;
  ARG * localARG;

  /**
     Constructor. Nothing to do.
  */
  argStatMiner();

  /**
     Constructor. Initializes the ARG.
  */
  

  /**
     This function obtains the stats for all sites with a certain derived
     allele count (DAC). It calls the getStatsForSite function for each site
     making sure that these sites get stored under the appropriate DAC. 
  */
  void getStatsByDAC(int derivedCount);

  /**
     This function obtains the stats such as core haplotype length, the length
     of second recombination and the counts of coalescing subtree for the lines
     with derived states at a given site. 
  */
  void getStatsForSite();
  
  /**
     Destructor. Empty the stats matrix. 
  */
  ~argStatMiner();

};
