#include "siteStat.h"


siteStat::siteStat() {
  lenCore[0] = lenCore[1] = -1;
  lenSecondRecomb[0] = lenSecondRecomb[1] = -1;
  leftConf[0] = leftConf[1] = -1;
  rightConf[0] = rightConf[1] = -1;
  frequency = 0.0;
}

bool siteStat::isEdge() {
  return ((lenSecondRecomb[0] == -1) || (lenSecondRecomb[1] == -1));
}

float siteStat::getPopProp(bool left=true) {
  return (left ? (leftConf[0]*1.0/(leftConf[0]+leftConf[1])) : (rightConf[0]/(rightConf[0]+rightConf[1])) );
}
