/**
   Site Statistics Class
   =====================
   
   This class is basically just a data structure to store
   the statistics for a site. Each site that is considered
   will have one of these structures here that will store 
   the information for that site. The infomation includes
   the length of the core haplotype, the length until the
   next recombination, the configuration (na, nb) of the
   subtree that this line coalesced into. It also includes
   if your first recombination is to core haplotype or not.

   Members of the class:
   ---------------------
   ### Attributes:###
   - fromPop2
   - lenCore
   - lenSecondRecomb
   - numPop1
   - numPop2
   - numCore
   - numNonCore
   - freq

   ### Methods:###
   - constructor
   - isEdge
   - getPopProp
   - destuctor

*/

#ifndef __SITESTAT_H__
#define __SITESTAT_H__

#include <utility>
#include <fstream>

using namespace std;

class siteStat {
 public:
  bool fromPop2; /**<Is the line sampled from population 1?*/
  int lenCore[2]; /**<Length of the core haplotype going left and right.*/
  int lenFirstRecomb[2]; /**<Length of segment from site to first recombination.*/
  int lenSecondRecomb[2]; /**<Length of segment from first to second recombination.*/
  int numPop1Core[2]; /**<When switching off core haplotype, count of pop1 in recombined-to subtree.*/
  int numPop2Core[2]; /**<When switching off core haplotype, count of pop2 in recombined-to subtree.*/
  int numPop1First[2]; /**<At first recombination, count of pop1 in recombined-to subtree.*/
  int numPop2First[2]; /**<At first recombination, count of pop2 in recombined-to subtree.*/
  float age;
  int freq1;
  int freq2;
  
  /**
     Constructor. Set all the array counts to -1 and frequency to -1.
  */
  siteStat();

  /**
     Function to return boolean indicating whether the site is part
     of a sequence at the edge of the simulate sequence - then the 
     left or right statistics will be default. 
  */
  bool isEdge();

  /**
     Returns the proportion of population 1 vs 2 samples in the subtree
     that the line of this site coalesced into, when switching off the core
     haplotype
  */
  float getPopPropCore(bool left);

  /**
     Is first recombination off core?
  */
  pair<bool, bool> isFirstOffCore();

  /**
     Print the site statistics.
  */
  void print(ofstream & output);

  /**
     Default destructor. Nothing to do.
   */
  ~siteStat() {}

};

#endif
