#include "treeStructure.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "writeTree.h"
#include "buildTree.h"
#include "destroyTree.h"
#include "stdbool.h"
// recursively visit the leaf nodes and create children
void growNode( FILE *fp, Node *node ) {
  int i;
  if( node->child[0] == NULL)
  {
    makeChildren(node);
    printOut( fp, node );
  }
  else {
    for ( i=0; i<4; ++i )
    {
      growNode( fp, node->child[i] );
      printOut( fp, node );
    }
  }
  return;
}


// grows each node of the tree
void growTree( Node *head ) {
  FILE *fp = fopen("quad.out","w"); // this is the output file that is used for the quad tree
  growNode(fp,head);
  fclose(fp);
  return;
}
