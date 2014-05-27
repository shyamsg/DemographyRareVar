#include "argHelper.h"

float argHelper::siteFreq(vector<bool> & polys) {
  float freq = 0.0;
  for (vector<bool>::iterator vit = polys.begin(); vit < polys.end(); vit++) {
    freq += (*vit ? 1:0);
  }
  return (freq/polys.size());
}

int argHelper::siteCount(vector<bool> & polys) {
  int count = 0.0;
  for (vector<bool>::iterator vit = polys.begin(); vit < polys.end(); vit++) {
    count += (*vit ? 1:0);
  }
  return count;
}

set<int> argHelper::getDerivedIndices(vector<bool> & polys) {
  set<int> chosen;
  int curLabel = 0;
  for (vector<bool>::iterator vit = polys.begin(); vit < polys.end(); vit++, curLabel++) {
    if (*vit) chosen.insert(curLabel);
  }
  return chosen;
}

