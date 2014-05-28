#include <boost/tokenizer.hpp>
#include "ARG.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

vector<bool> ARG::makeBitVector(string token) {
  vector<bool> vars(token.length());
  for (int i=0; i < token.length(); i++) {
    if (token[i] == '0')
      vars[i] = 0;
    else if (token[i] == '1')
      vars[i] = 1;
    else cerr << "Unknown snp state." << endl;
  }
  return vars;
}

void ARG::getVariants(string & line) {
  istringstream iss(line);
  string sub;
  for (int count=0; count < 6; count++, iss >> sub) {
    switch(count) {
    case 1:
    case 2: 
      break;
    case 3:
      variantPos.push_back(int(nearbyint(regionLength*stof(sub))));
      break;
    case 4:  
      mutTimes.push_back(stof(sub));
      break;
    case 5: 
      polymorphisms.push_back(makeBitVector(sub));
      break;
    }
  }
}

void ARG::getTree(string & line){
  string temp = line.substr(1,(line.find(sqClose)-1));
  treeSeqLengths.push_back(stoi(temp));
  temp = line.substr(line.find(sqClose)+1);
  // Variables for looping to make tree
  string::size_type sz;
  int countBracks = 0;
  int index = 0;
  bool leftTree = true;
  bool isName = true;
  // new tree - root node
  newickTreeNode * currentNode = new newickTreeNode;
  while(true) {
    switch(temp[index]) {
    case '(': 
      { //This is the beginning of a subtree, left-right separated by ','
	newickTreeNode * tempNode = new newickTreeNode;
	if (currentNode != NULL) {
	  tempNode->parent = currentNode;
	  currentNode->leftSubTree = tempNode;
	} 
	currentNode = tempNode;
	isName = true;
	countBracks++;
	break;
      }
    case ',':
      {
	isName = true;
	newickTreeNode * tempNode = new newickTreeNode;
	tempNode->parent = currentNode->parent;
	currentNode->parent->rightSubTree = tempNode;
	currentNode = tempNode;
	break;
      }
    case ':':
      {
	isName = false;
	break;
      }
    case ')':
      { // End of the subtree, go to parent
	currentNode = currentNode->parent;
	currentNode->leafList.insert(currentNode->leftSubTree->leafList.begin(), currentNode->leftSubTree->leafList.end());
	currentNode->leafList.insert(currentNode->rightSubTree->leafList.begin(), currentNode->rightSubTree->leafList.end());
	if (currentNode->leftSubTree->minLeafNode() > currentNode->rightSubTree->minLeafNode()) {
	  currentNode->switchNodes();
	}
	countBracks--;
	break;
      }
    default:
      {
	string temp1 = temp.substr(index);
	if (isName){
	  currentNode->leafList.insert(stoi(temp1, &sz));
	} else {
	  currentNode->branchLen = stof(temp1, &sz);
	}
	index += (sz - 1);
      }
    }
    index++;
    if (countBracks == 0 || index >= temp.length()) break;
  }
  treeList.push_back(currentNode);
}

void ARG::populateRecombList() {
  // Note: the recombList has 1 less entry than the treeList. 
  // The first entry of recombList is the difference between 
  // the first and second tree and so on.
  // treeList:  0 -> 1 -> 2 -> 3 -> 4 ... n-1 -> n
  //             \  / \  / \  / \  / \       \  /
  //              \/   \/   \/   \/   \       \/
  // recombList:   0    1    2    3    4       n-1
  // recombedTo:   0    1    2    3    4       n-1
  // recombedFrom: 0    1    2    3    4       n-1
  for (unsigned int tindex = 0; tindex < (this->treeList.size() - 1); tindex++) {
    recombList.push_back(treeList[tindex]->getRecombined(treeList[tindex+1]));
    recombedToList.push_back(treeList[tindex+1]->getRecombinedAdjoint(recombList.last()));
    recombedFromList.push_back(treeList[tindex]->getRecombinedAdjoint(recombList.last()));
  }
}


void ARG::parseMACSOutput(const char * macsFileName){
  ifstream macsfile(macsFileName);
  string line;
  if (macsfile.is_open()) {
    while(getline(macsfile, line)) {
      boost::tokenizer<> tok(line);
      boost::tokenizer<>::iterator tit = tok.begin();
      string firstToken = *tit;
      tit++;
      if (firstToken == "NEWICK") {
	string temp = line.substr(line.find(sqOpen));
	getTree(temp);
      } else {
	if (firstToken == "SITE") {
	  getVariants(line);
	} else {
	  if (firstToken == "COMMAND") {
	    tit++; tit++;
	    regionLength = stoi(*tit);
	  }
	}
      }
    }
  } else {
    cerr << "Unable to open file " << macsFileName << endl;
  }
  macsfile.close();
  // populate the recombination list
  populateRecombList();

#ifdef __DEBUG__
  cout << "Region length: " << regionLength << endl;
  cout << "Tree Sequence lengths: ";
  copy(treeSeqLengths.begin(), treeSeqLengths.end(), ostream_iterator<int>(cout, ",")); cout << endl;
  cout << "Variant positions: ";
  copy(variantPos.begin(), variantPos.end(), ostream_iterator<int>(cout, ",")); cout << endl;
  cout << "Polymorphic site states: " << endl;
  for (int i=0; i < polymorphisms.size(); i++) {
    copy(polymorphisms[i].begin(), polymorphisms[i].end(), ostream_iterator<bool>(cout, ""));
    cout << endl;
  }
  cout << "Tree list: " << endl;
  for (int i=0; i < treeList.size(); i++) { 
    treeList[i]->printTree();
  }
  cout << "Recombination list: " << recombList.size() << endl;
  for (int i=0; i < recombList.size(); i++) {
    cout << "Start - ";
    copy(recombList[i].begin(), recombList[i].end(), ostream_iterator<int>(cout, ","));
    cout << " - End" << endl;
  }
#endif
}

ARG::~ARG() {
  for(vector<newickTreeNode *>::iterator vit=treeList.begin(); vit<treeList.end(); vit++) {
    // Delete the individual trees
    delete *vit;
  }
  treeSeqLengths.clear();
  polymorphisms.clear();
  variantPos.clear();
  recombList.clear();
}
