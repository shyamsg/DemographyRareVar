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
  srand(time(NULL));
  seed = seed << 56 | rand();
  srand48(seed);
  cout << "Random seed: " << seed << endl;
  ARG myArg;
  myArg.parseMACSOutput(argv[1]);
  int maxDAC = atoi(argv[2]);
  argStatMiner myMiner(&myArg);
  myMiner.getStatsByDAC(1);
  cout << "Done with 1" << endl;
  ofstream test("test.out");
  myMiner.printStats(test);
  //  for(int count=0; count < maxDAC; count++)
  //    myMiner.getStatsByDAC(count);
}
