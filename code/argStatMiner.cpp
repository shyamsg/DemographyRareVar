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
  uint i, j; // loop indices
  set<int>::iterator sit; // set iterator
  uint index = (left ? 0 : 1);
  int increment = (left ? -1 : 1);

  // Each sample that carries the derived allele will have a vector of these pairstats -
  // tracing their lineage back to root.
  newickTreeNode * curTree = localARG->treeList[treeIndex];

  // For each of the lineages that need to be looked at, keep track of the 
  vector<int> nrecomb = vector<int>(DAC, 0);
  // Go from current tree + 1 to the last or till all the stats are collected.
  for (i = treeIndex+increment; (left ? (i >= 0) : (i < localARG->treeList.size())) ; i+=increment) {
    // For the current tree, find the lineages and process to see if the current 
    // lineage went through a recombination. If it did measure the appropriate stats 
    curTree = localARG->treeList[i];
  }
}

void argStatMiner::extractRecombination(newickTreeNode * first, newickTreeNode * second) {
}
