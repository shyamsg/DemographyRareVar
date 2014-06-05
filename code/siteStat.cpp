#include "siteStat.h"
#include <iostream>

siteStat::siteStat() {
  fromPop2 = false;
  lenCore[0] = lenCore[1] = -1;
  lenFirstRecomb[0] = lenFirstRecomb[1] = -1;
  lenSecondRecomb[0] = lenSecondRecomb[1] = -1;
  numPop1Core[0] = numPop1Core[1] = 0;
  numPop2Core[0] = numPop2Core[1] = 0;
  numPop1First[0] = numPop1First[1] = 0;
  numPop2First[0] = numPop2First[1] = 0;
  freq1 = 0;
  freq2 = 0;
}

bool siteStat::isEdge() {
  return ((lenCore[0] == -1) || (lenCore[1] == -1));
}

float siteStat::getPopPropCore(bool left=true) {
  if (left) { 
    if ((numPop1Core[0]+numPop2Core[0]) == 0)
      return (numPop1Core[0]*1.0/(numPop1Core[0]+numPop2Core[0]));
    else return -1;
  } else {
    if ((numPop1Core[1]+numPop2Core[1]) == 0)
      return (numPop1Core[1]*1.0/(numPop1Core[1]+numPop2Core[1]));
    else return -1;
  }
}

pair<bool, bool> siteStat::isFirstOffCore() {
  pair<bool, bool> temp;
  if (lenCore[0] == lenFirstRecomb[0])
    temp.first = true;
  else temp.first = false;
  if (lenCore[1] == lenFirstRecomb[1])
    temp.second = true;
  else temp.second = false;
  return temp;
}

void siteStat::print(ofstream & output) {
  output << (int)fromPop2+1 << "\t";
  output << age << "\t" << freq1 << "\t" << freq2 << "\t";
  output << lenCore[0] << "\t" << lenCore[1] << "\t";
  output << lenFirstRecomb[0] << "\t" << lenFirstRecomb[1] << "\t";
  output << lenSecondRecomb[0] << "\t" << lenSecondRecomb[1] << "\t";
  output << numPop1Core[0] << "\t" << numPop1Core[1] << "\t";
  output << numPop2Core[0] << "\t" << numPop2Core[1] << "\t";
  output << numPop1First[0] << "\t" << numPop1First[1] << "\t";
  output << numPop2First[0] << "\t" << numPop2First[1] << endl;
}
