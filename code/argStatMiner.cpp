#include "argStatMiner.h"

argStatMiner::argStatMiner() {
  // Nothing to do yet. Might change in the near future. 
}

argStatMiner::argStatMiner(ARG *topARG) {
  localARG = topARG;
}

void argStatMiner::getStatsByDAC(int derivedCount) {

}

void argStatMiner::getStatsForSite() {
  // Compute the length till first recombination out of core haplotype to
  // the left and right.

  // Keep track of which lineage it joins - from this extract the number
  // of pop1 and pop2 members in that subtree.

}
