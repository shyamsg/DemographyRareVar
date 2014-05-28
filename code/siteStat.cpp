#include "siteStat.h"

siteStat::siteStat() {
  fromPop1 = true;
  lenCore[0] = lenCore[1] = -1;
  lenFirstRecomb[0] = lenFirstRecomb[1] = -1;
  lenSecondRecomb[0] = lenSecondRecomb[1] = -1;
  numPop1Core[0] = numPop1Core[1] = -1;
  numPop2Core[0] = numPop2Core[1] = -1;
  numPop1First[0] = numPop1First[1] = -1;
  numPop2First[0] = numPop2First[1] = -1;
  frequency = 0.0;
}

bool siteStat::isEdge() {
  return ((lenCore[0] == -1) || (lenCore[1] == -1));
}

float siteStat::getPopPropCore(bool left=true) {
  return (left ? (numPop1Core[0]*1.0/(numPop1Core[0]+numPop2Core[0])) : (numPop1Core[1]*1.0/(numPop1Core[1]+numPop2Core[1])) );
}

pair<bool, bool> siteStat::isFirstOffCore() {
  pair<bool, bool> temp;
  if (lenCore[0] == lenFirst[0])
    temp.first = true;
  else temp.first = false;
  if (lenCore[1] == lenFirst[1])
    temp.second = true;
  else temp.second = false;
  return temp;
}

