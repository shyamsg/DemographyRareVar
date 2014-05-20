#include "argStatMiner.h"

argStatMiner::argStatMiner() {
  // Nothing to do yet. Might change in the near future. 
}

argStatMiner::argStatMiner(ARG *topARG) {
  localARG = topARG;
}

void argStatMiner::getStatsByDAC(int maxDerivedCount) {
  // Test sites to see if this site's dac fits the bill
  // If it does, then do stuff for this site. 
  
  
}

void argStatMiner::getStatsForSite(set<int> &chosenLabels) {
  // Compute the length till first recombination out of core haplotype to
  // the left and right.

  // Keep track of which lineage it joins - from this extract the number
  // of pop1 and pop2 members in that subtree.

  // Compute the length of the second recombination

}
