// include statemtns
#include "treeStructure.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "writeTree.h"
#include "buildTree.h"
#include "destroyTree.h"
#include "tests.h"
#include "valueTree.h"
#include "stdbool.h"


void indicateNode(Node *node, int* numberOfFalseResultsPointer, double tolerence, int choice) {
  int i;
  if( node->child[0] == NULL )
  {
    if(indicator(node,tolerence,choice) == false)
    {
      makeChildren(node);
      (*numberOfFalseResultsPointer) ++; // Incrament the number of false values through a pointer
    }
  }
  else {
    for ( i=0; i<4; ++i )
    {
      indicateNode(node->child[i], numberOfFalseResultsPointer, tolerence,choice); // recursively call nodes
    }
  }
  return;
}

void treeGenerator( Node *head, double tolerence, int choice )
{
  int numberOfFalseResults = 1; // sets to a non 0 so it can start the while loop
  int* numberOfFalseResultsPointer = &numberOfFalseResults;

  while(numberOfFalseResults != 0)
  {
    *numberOfFalseResultsPointer = 0;
    indicateNode(head,numberOfFalseResultsPointer,tolerence,choice); // this function can change numberOfFalseResults to a non 0 number.
  }
}
