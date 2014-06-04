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
  seed = 6773413840411030749;
  srand48(seed);
  cout << "Random seed: " << seed << endl;
  ARG myArg;
  myArg.parseMACSOutput(argv[1]);
  int maxDAC = atoi(argv[2]);
  argStatMiner myMiner(&myArg);
  myMiner.getStatsByDAC(maxDAC);
  ofstream outfile(argv[3]);
  outfile << "Pop\tDAC\tcoreLeft\tcoreRight\tfirstLeft\tfirstRight\tsecondLeft\tsecondRight\tpop1CoreLeft\tpop1CoreRight\tpop2CoreLeft\tpop2coreRight\tpop1FirstLeft\tpop1FirstRight\tpop2FirstLeft\tpop2FirstRight" << endl;
  myMiner.printStats(outfile);
}
