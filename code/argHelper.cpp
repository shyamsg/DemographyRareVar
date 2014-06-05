#include "argHelper.h"

float argHelper::siteFreq(vector<bool> & polys) {
  float freq = 0.0;
  for (vector<bool>::iterator vit = polys.begin(); vit < polys.end(); vit++) {
    freq += (*vit ? 1:0);
  }
  return (freq/polys.size());
}

pair<int, int> argHelper::siteCount(vector<bool> & polys, int pop1size) {
  pair<int, int> count;
  count.first = 0;
  count.second = 0;
  int index = 0;
  for (vector<bool>::iterator vit = polys.begin(); vit < polys.end(); vit++, index++) {
    if (index < pop1size) {
      count.first += (*vit ? 1:0); 
    } else {
      count.second += (*vit ? 1:0); 
    }
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

