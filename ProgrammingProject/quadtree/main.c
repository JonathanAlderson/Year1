#include "treeStructure.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "writeTree.h"
#include "buildTree.h"
#include "destroyTree.h"
#include "tests.h"
#include "math.h"
#include "stdbool.h"
#include  "valueTree.h"
#include "stdbool.h"
// main //

//global variable
int maxTreeLevel = 5;

int main( int argc, char **argv ) {




  char in;

  // just a nice enter message for the user
  printf("\e[1;1H\e[2J"); // clears the screen
  printf("\n\n\n\n   ____                  _ _                   _______        _       ");
  printf("\n  / __ \\                | | |                 |__   __|      | |      ");
  printf("\n | |  | |_   _  __ _  __| | |_ _ __ ___  ___     | | ___  ___| |_ ___");
  printf("\n | |  | | | | |/ _` |/ _` | __| '__/ _ \\/ _ \\    | |/ _ \\/ __| __/ __|");
  printf("\n | |__| | |_| | (_| | (_| | |_| | |  __/  __/    | |  __/\\__ \\ |_\\__ \\");
  printf("\n  \\____\\_\\__,_|\\__,_|\\__,_|\\__|_|  \\___|\\___|    |_|\\___||___/\\__|___/\n\n\n");

  printf("\nA: Destroy Tree: Full Tree Level 2");
  printf("\nB: Destroy Tree: Non-Uniform Tree Level 3");
  printf("\n\nC: Grow Tree: Full Tree Level 2");
  printf("\nD: Grow Tree: Non-Uniform Tree Level 3");
  printf("\n\nE: Limit Tree: Non-Uniform Tree Level 3, MaxLevel = 3");
  printf("\nF: Limit Tree: Non-Uniform Tree Level 3, MaxLevel = 4");
  printf("\n\nG: data-dependent: Run the Indicator and DataFunctions Tolerence 0.5, Choice 0");
  printf("\nH: data-dependent: Run the Indicator and DataFunctions Tolerence 0.5, Choice 1");
  printf("\nI: data-dependent: Run the Indicator and DataFunctions Tolerence 0.5, Choice 2");

  printf("\n\n\nPlease enter your selection in upper case: ");
  scanf(" %c",&in);

  // Calls a different test case depending on what the user inputs
  switch(in)
  {
    case 'A':
      testA();
      break;
    case 'B':
      testB();
      break;
    case 'C':
      testC();
      break;
    case 'D':
      testD();
      break;
    case 'E':
      testE();
      break;
    case 'F':
      testF();
      break;
    case 'G':
      testG();
      break;
    case 'H':
      testH();
      break;
    case 'I':
      testI();
      break;
  }

  return 0;
}
