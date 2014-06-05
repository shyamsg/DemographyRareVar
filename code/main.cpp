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
  ofstream outfile(argv[3]);
  outfile << "COMMAND:";
  for (int i = 0; i < argc; i++)
    outfile << " " << argv[i];
  outfile << endl;
  outfile << "SEED: " << seed << endl;
  ARG myArg;
  cerr << "Parsing ARG ..." << endl;
  myArg.parseMACSOutput(argv[1]);
  cerr << "Done parsing ARG." << endl;
  int maxDAC = atoi(argv[2]);
  cerr << "Mining stats ..." << endl;
  argStatMiner myMiner(&myArg);
  outfile << "Pop\tDAC\tcoreLeft\tcoreRight\tfirstLeft\tfirstRight\tsecondLeft\tsecondRight\tpop1CoreLeft\tpop1CoreRight\tpop2CoreLeft\tpop2coreRight\tpop1FirstLeft\tpop1FirstRight\tpop2FirstLeft\tpop2FirstRight" << endl;
  myMiner.getStatsByDAC(maxDAC, outfile);
  cerr << "Done mining stats." << endl;
  cerr << "Writing output ..." << endl;
  myMiner.printStats(outfile);
  cerr << "Done writing output." << endl;
}
