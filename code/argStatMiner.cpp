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
  uint curTreeIndex = -1;
  uint totalTreeLengths = 0;
  for (uint cnt=0; cnt < numsites; cnt++) {
    if (localARG->variantPos[cnt] > totalTreeLengths) {
      curTreeIndex++;
      totalTreeLengths += treeSeqLengths[curTreeIndex];
    }
    vector<bool> & curPoly = localARG->polymorphisms[cnt];
    int curDAC = helper.siteCount(curPoly);
    // Site's DAC is greater than threshold.
    if (curDAC > maxDerivedCount) continue;
    getStatsForSite(helper.getDerivedIndices(curPoly), curTreeIndex);
  }
}

void argStatMiner::getStatsForSite(set<int> chosenLabels, uint treeIndex) {
  // Get the tree for this site
  
  // Compute the length till first recombination out of core haplotype to
  // the left and right.

  // Keep track of which lineage it joins - from this extract the number
  // of pop1 and pop2 members in that subtree.

  // Compute the length of the second recombination

}
