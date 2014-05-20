/**
   ARG helper class
   ================

   This class is a helper class which implements some functions
   for the ARG class. It implements functions like the frequency
   calculator, derived allele count calculator... etc. 

   Members fo the class:
   ---------------------
   ### Attributes:###
   
   ### Methods:###
   - siteFreq
   - siteCount

*/

#include <vector>
#include <set>

using namespace std;

class argHelper {
 public:
  /**
     Calculates the allele frequency of the given site
  */
  float siteFreq(vector<bool> & polys);

  /**
     Calculates the derived allele count of the given site
  */
  int siteCount(vector<bool> & polys);

  /**
     Gets the indices of samples that carry derived allele
  */
  set<int> getDerivedIndices(vector<bool> & polys);
};
