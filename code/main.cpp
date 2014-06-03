/**
   MAIN
   ====
   This is a temporary test main function.
*/

#include <iostream>
#include <fstream>
#include <iterator>
#include <tclap/CmdLine.h>
#include <ctime>
#include "ARG.h"
#include "argStatMiner.h"

using namespace std;

int main(int argc, char * argv[])
{
  unsigned long seed = (time(NULL)<<4)^0x31F29B378728B8EE;
  srand48(seed);
  ARG myArg;
  myArg.parseMACSOutput(argv[1]);
  for (int i = 0; i < myArg.recombList.size(); i++) {
    if (myArg.recombedFromList[i] == myArg.recombedToList[i]) {
      cout << "Equal: ";
      copy(myArg.recombedFromList[i].begin(), myArg.recombedFromList[i].end(), ostream_iterator<int>(cout, ",")); cout << endl;
    } else {
      cout << "Not equal" << endl;
      copy(myArg.recombedFromList[i].begin(), myArg.recombedFromList[i].end(), ostream_iterator<int>(cout, ",")); cout << endl;
      copy(myArg.recombedToList[i].begin(), myArg.recombedToList[i].end(), ostream_iterator<int>(cout, ",")); cout << endl;
    }
  }
  int maxDAC = atoi(argv[2]);
  argStatMiner myMiner(&myArg);
  myMiner.getStatsByDAC(1);
  cout << "Done with 1" << endl;
  ofstream test("test.out");
  myMiner.printStats(test);
  //  for(int count=0; count < maxDAC; count++)
  //    myMiner.getStatsByDAC(count);
}
