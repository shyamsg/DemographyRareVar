#include <boost/tokenizer.hpp>
#include "ARG.h"
#include <iostream>
#include <fstream>

void ARG::getVariants(string & line) {
}

void ARG::getTree(string & line){
}

void ARG::parseMACSOutput(char * macsFileName){
  ifstream macsfile(macsFileName);
  string line;
  if (macsfile.is_open()) {
    while(getline(macsfile, line)) {
      tokenizer<> tok(line);
      switch(*(tok.begin())) {
      case "NEWICK":
	getTree(line);
	break;
      case "SITE":
	getVariants(line);
      case "SEED":
      case "COMMAND":
	break;
      default:
	cout << "First token not recognized in line:" << line << endl;	
      }
    }
  } else {
    cerr << "Unable to open file " << macsFileName << endl;
  }
  macsfile.close();
}

ARG::~ARG() {
  for(vector<newickTreeNode *>::iterator vit=treeList.begin(); vit++; vit<treeList.end()) {
    // Delete the individual trees
    delete *vit;
  }
  treeSeqLengths.clear();
  polymorphisms.clear();
  variantPos.clear();
}
