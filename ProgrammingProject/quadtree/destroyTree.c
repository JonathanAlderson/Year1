#include "treeStructure.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "writeTree.h"
#include "buildTree.h"
#include "destroyTree.h"
#include "stdbool.h"

// frees all of the memory used during execution
void destroyTree( Node *head ) {
  destroyNode(head);
  return;
}

void destroyNode(Node *node ) {
  int i;
  if( node->child[0] == NULL )
  {
    free(node); // frees memory

  }
  else
  {
    for ( i=0; i<4; ++i )
    {
      destroyNode(node->child[i]); // recursively called
    }
    free(node); // frees memory

  }
  return;
}
