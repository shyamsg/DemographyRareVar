/**
   MAIN
   ====
   This is a temporary test main function.
*/

#include <iostream>
#include <tclap/CmdLine.h>
#include "ARG.h"

int main(int argc, char * argv[])
{
  ARG myArg;
  myArg.parseMACSOutput(argv[1]);
  
}
