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
  uint numsites = localARG->mutTimes.size();
  for (uint cnt=0; cnt < numsites; cnt++) {
    vector<bool> & curPoly = polymorphisms[cnt];
    int curDAC = helper.siteCount(curPoly);
    // Site's DAC is greater than threshold.
    if (curDAC > maxDerivedCount) continue;
    getStatsForSite(helper.getDerivedIndices(curPoly));
  }
}

void argStatMiner::getStatsForSite(set<int> &chosenLabels) {
  // Compute the length till first recombination out of core haplotype to
  // the left and right.

  // Keep track of which lineage it joins - from this extract the number
  // of pop1 and pop2 members in that subtree.

  // Compute the length of the second recombination

}
