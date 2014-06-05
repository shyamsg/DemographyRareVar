#include "argStatMiner.h"
#include <iostream>

argStatMiner::argStatMiner() {
  // Nothing to do yet. Might change in the near future. 
}

argStatMiner::argStatMiner(ARG *topARG) {
  localARG = topARG;
}

void argStatMiner::getStatsByDAC(int maxDerivedCount, ofstream & outfile) {
  // Test sites to see if this site's dac fits the bill
  // If it does, then do stuff for this site. 
  uint numsites = localARG->mutTimes.size();
  uint curTreeIndex = -1;
  uint totalTreeLengths = 0;
  for (uint cnt=0; cnt < numsites; cnt++) {
    while (localARG->variantPos[cnt] > totalTreeLengths) {
      curTreeIndex++;
      totalTreeLengths += localARG->treeSeqLengths[curTreeIndex];
    }
    if (cnt % 100 == 0) {
      cerr << "Processed " << cnt << " sites." << endl;
      cerr.flush();
      this->printStats(outfile);
      outfile.flush();
      statVector.clear();
    }
    vector<bool> & curPoly = localARG->polymorphisms[cnt];
    pair<int, int> curDACs = helper.siteCount(curPoly, localARG->pop1Size);
    // Site's DAC is greater than threshold.
    if (curDACs.first > maxDerivedCount || curDACs.second > maxDerivedCount) continue;
    if (curDACs.first == 0 && curDACs.second == 0) continue;
    // Get stats for this site - compute the left and right lengths
    // on this sequence before switching trees - leftOnTree and rightOnTree.
    // computed with respect to the current poly's position. 
    int leftOnTree = localARG->variantPos[cnt] - (totalTreeLengths - localARG->treeSeqLengths[curTreeIndex]);
    int rightOnTree = totalTreeLengths - localARG->variantPos[cnt];
    //    cerr << "Info " << curDACs.first << " " << curDACs.second  << " " << leftOnTree << " " << rightOnTree << endl;
    getStatsForSite(helper.getDerivedIndices(curPoly), curTreeIndex, leftOnTree, rightOnTree, curDACs, localARG->mutTimes[cnt]);
  }
}

void argStatMiner::getStatsForSite(set<int> chosenLabels, uint treeIndex, int leftOnTree, int rightOnTree, pair<int, int> curDACs, float age) {
  uint DAC = chosenLabels.size();
  vector<siteStat> stats = vector<siteStat>(DAC);
  set<int>::iterator sit = chosenLabels.begin(); 
  for(uint i = 0; i < DAC; i++, sit++) {
    stats[i].fromPop2 = (*sit >= localARG->pop1Size);
    stats[i].freq1 = curDACs.first;
    stats[i].freq2 = curDACs.second;
    stats[i].age = age;
    stats[i].lenCore[0] = stats[i].lenFirstRecomb[0] = leftOnTree;
    stats[i].lenCore[1] = stats[i].lenFirstRecomb[1] = rightOnTree;
    stats[i].lenSecondRecomb[0] = stats[i].lenSecondRecomb[1] = 0;
  }
  getStatsDirection(chosenLabels, treeIndex, stats, true);
  getStatsDirection(chosenLabels, treeIndex, stats, false);
  statVector.push_back(stats);
}

void argStatMiner::getStatsDirection(set<int> chosenLabels, uint treeIndex, vector<siteStat> & stats, bool left) {
  uint DAC = chosenLabels.size();
  set<int>::iterator sit;
  int i, j; // loop indices
  int pop1Size = localARG->pop1Size;

  // Moving from this tree to the last one, keep track of how many recombinations etc, their lengths etc. 
  vector<int> numRecomb = vector<int>(DAC, 0);
  vector<bool> onCore = vector<bool>(DAC, true);
  set<int> stillOnCore = chosenLabels;
  // Cases to consider 
  // moving left - first tree encountered is your own - then you must check the recombList between your
  // own and previous - if chosen line is part of the recombined set then you must adjust the stats 
  // accordingly -
  // Changes made to compute the recombTo and recombFrom List and times on the fly - to save memory
  // Important to check how much memory this saves.
  if (left) {
    for (i = treeIndex - 1; i >= 0 ; i--) {
      set<int> & recombed = localARG->recombList[i];
      j = 0;
      // recombedFrom replaced by on the fly call
      //      set<int> recombedFromList = localARG->treeList[i]->getRecombinedAdjoint(localARG->recombList[i]);
      //      float recombFromTime = localARG->treeList[i]->findMRCANode(localARG->recombList[i])->getTotalTime();
      int pop1ontree = pop1OnTree(localARG->recombedFromList[i], pop1Size);
      int pop2ontree = localARG->recombedFromList[i].size() - pop1ontree;
      bool offcore = isOffCore(localARG->recombedFromList[i], stillOnCore, localARG->recombFromTimes[i], localARG->mutTimes[treeIndex]);
      for (sit = chosenLabels.begin(); sit != chosenLabels.end(); sit++, j++) {
	if (!onCore[j] && numRecomb[j] > 1) continue; // already measured upto 2 recombs and offCore
	if (recombed.find(*sit) != recombed.end()) { // this line recombined off
	  // set the count variables correctly
	  if (numRecomb[j] == 0) { //firstRecomb
	    stats[j].numPop1First[0] = pop1ontree;
	    stats[j].numPop2First[0] = pop2ontree;
	  }
	  if (offcore && onCore[j]) { //off core now
	    stats[j].numPop1Core[0] = pop1ontree;
	    stats[j].numPop2Core[0] = pop2ontree;
	    stillOnCore.erase(*sit);
	    onCore[j] = false;
	  }
	  numRecomb[j]++;
	}
	// Increment the lengths - according to which one you are measuring.
	if (onCore[j])
	  stats[j].lenCore[0] += localARG->treeSeqLengths[i]; 
	switch(numRecomb[j]) {
	case 0:
	  stats[j].lenFirstRecomb[0]+= localARG->treeSeqLengths[i];
	  break;
	case 1:
	  stats[j].lenSecondRecomb[0] += localARG->treeSeqLengths[i];
	  break;
	default: break;
	}
      }
    }
  } else { // moving right - first tree encountered is the next one so keep going to the end. 
    for (i = treeIndex; i < (localARG->treeList.size() - 1) ; i++) {
      set<int> recombed = localARG->recombList[i];
      j = 0;
      // recombedTo replaced by on the fly call
      //      set<int> recombedToList = localARG->treeList[i+1]->getRecombinedAdjoint(localARG->recombList[i]);
      //      float recombToTime = localARG->treeList[i+1]->findMRCANode(localARG->recombList[i])->getTotalTime();
      int pop1ontree = pop1OnTree(localARG->recombedToList[i], pop1Size);
      int pop2ontree = localARG->recombedToList[i].size() - pop1ontree;
      bool offcore = isOffCore(localARG->recombedToList[i], stillOnCore, localARG->recombToTimes[i], localARG->mutTimes[treeIndex]);
      for (sit = chosenLabels.begin(); sit != chosenLabels.end(); sit++, j++) {
	if (!onCore[j] && numRecomb[j] > 1) continue; // already measured upto 2 recombs and offCore
	if (recombed.find(*sit) != recombed.end()) { // this line recombined off
	  // set the count variables correctly
	  if (numRecomb[j] == 0) { //firstRecomb
	    stats[j].numPop1First[1] = pop1ontree;
	    stats[j].numPop2First[1] = pop2ontree;
	  }
	  if (offcore && onCore[j]) { //off core now
	    stats[j].numPop1Core[1] = pop1ontree;
	    stats[j].numPop2Core[1] = pop2ontree;
	    stillOnCore.erase(*sit);
	    onCore[j] = false;
	  }
	  numRecomb[j]++;
	}
	// Increment the lengths - according to which one you are measuring.
	if (onCore[j])
	  stats[j].lenCore[1] += localARG->treeSeqLengths[i+1]; 
	switch(numRecomb[j]) {
	case 0:
	  stats[j].lenFirstRecomb[1]+= localARG->treeSeqLengths[i+1];
	  break;
	case 1:
	  stats[j].lenSecondRecomb[1] += localARG->treeSeqLengths[i+1];
	  break;
	default: break;
	}
      }
    }
  }
}

int argStatMiner::pop1OnTree(set<int> leaves, int pivot) {
  int result = 0;
  for (set<int>::iterator sit = leaves.begin(); sit != leaves.end(); sit++) {
    if (*sit < pivot) result++;
  }
  return result;
}

bool argStatMiner::isOffCore(set<int> leaves, set<int> core, float recombTime, float mutTime) {
  // Core is the set of original mutation carrying leaves that still 
  // stay on the core haploytpe. 
  // The way to check if the the recombined went onto core or not
  // is to check these things
  // 1. A subset of the core haplotypes must be on the recombined to tree.
  // 2. The recombination time - the time at which the recombed lines join
  // the new tree is less than mutation time.
  // If the recombed lines join a tree with at least some of the lines with core
  // (less than all), then the 

  int coreInTree = 0;
  for (set<int>::iterator sit = core.begin(); sit != core.end(); sit++) {
    if (leaves.find(*sit) != leaves.end()) // cannot find one of the leaves
      coreInTree++;
  }
  return (coreInTree > 0 && coreInTree < core.size()) || (coreInTree == core.size() && recombTime < mutTime); 
}

void argStatMiner::printStats(ofstream & output) {
  for (vector<vector<siteStat> >::iterator vvit = statVector.begin(); vvit < statVector.end(); vvit++) {
    for (vector<siteStat>::iterator vit = vvit->begin(); vit < vvit->end(); vit++) {
      vit->print(output);
    }
  }
}

argStatMiner::~argStatMiner(){
  // Should delete all the different stat vectors - no longer necessary since it is a vector of vectors
}
