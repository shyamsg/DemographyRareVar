#include "siteStat.h"

siteStat::siteStat() {
  lenCore[0] = lenCore[1] = -1;
  lenSecondRecomb[0] = lenSecondRecomb[1] = -1;
  numPop1[0] = numPop1[1] = -1;
  numPop2[0] = numPop2[1] = -1;
  frequency = 0.0;
}

bool siteStat::isEdge() {
  return ((lenCore[0] == -1) || (lenCore[1] == -1));
}

float siteStat::getPopProp(bool left=true) {
  return (left ? (numPop1[0]*1.0/(numPop1[0]+numPop2[0])) : (numPop1[1]*1.0/(numPop1[1]+numPop2[1])) );
}
