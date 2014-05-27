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
      totalTreeLengths += localARG->treeSeqLengths[curTreeIndex];
    }
    vector<bool> & curPoly = localARG->polymorphisms[cnt];
    int curDAC = helper.siteCount(curPoly);
    // Site's DAC is greater than threshold.
    if (curDAC > maxDerivedCount) continue;
    // Get stats for this site - compute the left and right lengths
    // on this sequence before switching trees - leftOnTree and rightOnTree.
    // computed with respect to the current poly's position. 
    uint leftOnTree = localARG->variantPos[cnt] - (totalTreeLengths - localARG->treeSeqLengths[curTreeIndex]);
    uint rightOnTree = totalTreeLengths - localARG->variantPos[cnt];
    getStatsForSite(helper.getDerivedIndices(curPoly), curTreeIndex, leftOnTree, rightOnTree);
  }
}

void argStatMiner::getStatsForSite(set<int> chosenLabels, uint treeIndex, uint leftOnTree, uint rightOnTree) {
  uint DAC = chosenLabels.size();
  siteStat* stats = new siteStat[DAC];
  for(uint i = 0; i < DAC; i++) {
    stats[i].frequency = DAC;
    stats[i].lenCore[0] = leftOnTree;
    stats[i].lenCore[1] = rightOnTree;
    stats[i].lenSecondRecomb[0] = stats[i].lenSecondRecomb[1] = 0;
  }
  getStatsDirection(chosenLabels, treeIndex, stats, true);
  getStatsDirection(chosenLabels, treeIndex, stats, false);
}

void argStatMiner::getStatsDirection(set<int> chosenLabels, uint treeIndex, siteStat * stats, bool left) {
  uint DAC = chosenLabels.size();
  set<int>::iterator sit;
  uint i, j; // loop indices
  uint index = (left ? 0 : 1);
  int increment = (left ? -1 : 1);

  // Moving from this tree to the last one, keep track of how many recombinations etc, their lengths etc. 
  vector<int> numRecomb = vectos<int>(DAC, 0);
  uint recombIndex;
  int recombShift = (left ? -1 : 0);
  // Cases to conside 
  // moving left - first tree encountered is your own - then you must check the recombList between your
  // own and previous - if chosen line is part of the recombined set then you must adjust the stats 
  // accordingly -
  // moving right - first tree encountered is the next one
  for (i = treeIndex+index; (left ? (i >= 0) : (i < localARG->treeList.size())) ; i+=increment) {
    recombIndex = 
  }
}
