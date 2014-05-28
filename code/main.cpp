/**
   MAIN
   ====
   This is a temporary test main function.
*/

#include <iostream>
#include <tclap/CmdLine.h>
#include <ctime>
#include "ARG.h"
#include "argStatMiner.h"

int main(int argc, char * argv[])
{
  unsigned long seed = (time(NULL)<<4)^0x31F29B378728B8EE;
  srand48(seed);
  ARG myArg;
  myArg.parseMACSOutput(argv[1]);
  myArg.pop1Size = 1000;
  int maxDAC = atoi(argv[2]);
  argStatMiner myMiner(&myArg);
  for(int count=0; count < maxDAC; count++)
    myMiner.getStatsByDAC(count);
}
