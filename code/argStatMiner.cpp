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
  siteStat* stats = new siteStat[chosenLabels.size()];
  getStatsRight(chosenLabels, treeIndex, rightOnTree, stats);
  getStatsLeft(chosenLabels, treeIndex, leftOnTree, stats);
}

void argStatMiner::getStatsRight(set<int> chosenLabels, uint treeIndex, uint remTree, siteStat * stats) {
  uint DAC = chosenLabels.size();
  // Initialize the stats with the remaining on tree stuff
  for (uint i = 0; i < DAC; i++) {
    stats[i].lenCore[1] = remTree;
  }
  // Each sample that carries the derived allele will have a vector of these pairstats -
  // tracing their lineage back to root.
  newickTreeNode * curTree = localARG->treeList[treeIndex];
  vector<vector<pairstat> > siteInfo = vector<vector<pairstat> >(DAC); 
  for (uint i = 0, set<int>::iterator sit = chosenLabels.begin(); sit != chosenLabels.end(); sit++, i++) {
    siteInfo[i] = curTree->curTree.getLineage(*sit);
  }
  vector<int> nrecomb = vector<int>(DAC, 0)
  for (uint i = treeIndex+1; i < localARG->treeList.size(); i++) {
    
  }
  // Compute the length till first recombination out of core haplotype to
  // the right.


  // Keep track of which lineage it joins - from this extract the number
  // of pop1 and pop2 members in that subtree.

  // Compute the length of the second recombination

}

void argStatMiner::getStatsLeft(set<int> chosenLabels, uint treeIndex, uint remTree, siteStat * stats) {

  // Compute the length till first recombination out of core haplotype to
  // the left.


  // Keep track of which lineage it joins - from this extract the number
  // of pop1 and pop2 members in that subtree.

  // Compute the length of the second recombination

}

