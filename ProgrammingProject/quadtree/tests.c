// include statments
#include "treeStructure.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "writeTree.h"
#include "buildTree.h"
#include "destroyTree.h"
#include "tests.h"
#include "indicator.h"
#include "stdbool.h"


// Destroy Level two tree
void testA()
{
  printf("\nStarting Test A\nDestroy Tree: Full Tree Level 2\n\n");

  // make the head node
  Node *head;
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  makeChildren( head );
  makeChildren( head->child[0]);
  makeChildren( head->child[1]);
  makeChildren( head->child[2]);
  makeChildren( head->child[3]);



  // print the tree for Gnuplot
  writeTree( head );

  //Destroys tree
  destroyTree(head);
}

// Destroy an uneven level three tree
void testB()
{
  printf("\nStarting Test B\nDestroy Tree: Non-Uniform Tree Level 3\n\n");

  // make the head node
  Node *head;
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  makeChildren( head );
  makeChildren( head->child[0]);
  makeChildren( head->child[1]);
  makeChildren( head->child[2]);
  makeChildren( head->child[3]);
  makeChildren( head->child[2]->child[1]);
  makeChildren( head->child[3]->child[2]);

  // print the tree for Gnuplot
  writeTree( head );

  //Destroys tree
  destroyTree(head);
}

// Grow Tree: Full Tree Level 2
void testC()
{
  printf("\nStarting Test C\nGrow Tree: Full Tree Level 2\n\n");


  // make the head node
  Node *head;
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  makeChildren( head );
  makeChildren( head->child[0]);
  makeChildren( head->child[1]);
  makeChildren( head->child[2]);
  makeChildren( head->child[3]);

  // grow the tree

  growTree(head);

  // print the tree for Gnuplot
  writeTree( head );

  //Destroys tree
  destroyTree(head);
}

//Grow Tree: Non-Uniform Tree Level 3
void testD()
{
  printf("\nStarting Test D\nGrow Tree: Non-Uniform Tree Level 3\n\n");
  // make the head node
  Node *head;
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  makeChildren( head );
  makeChildren( head->child[0]);
  makeChildren( head->child[1]);
  makeChildren( head->child[2]);
  makeChildren( head->child[3]);
  makeChildren( head->child[0]->child[0]);
  makeChildren( head->child[1]->child[2]);

  // grow the tree

  growTree(head);

  // print the tree for Gnuplot
  writeTree( head );

  //Destroys tree
  destroyTree(head);
}

// Limit Tree: Non-Uniform Tree Level 3, MaxLevel = 3
void testE()
{
  printf("\nStarting Test E\n\nLimit Tree: Non-Uniform Tree Level 3, MaxLevel = 3\n");
  maxTreeLevel = 3;

  // make the head node
  Node *head;
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  makeChildren( head );
  makeChildren( head->child[0]);
  makeChildren( head->child[1]);
  makeChildren( head->child[2]);
  makeChildren( head->child[3]);
  makeChildren( head->child[0]->child[0]);
  makeChildren( head->child[1]->child[2]);

  // grow the tree

  growTree(head);
  growTree(head);

  // print the tree for Gnuplot
  writeTree( head );

  //Destroys tree
  destroyTree(head);
}
// Limit Tree: Non-Uniform Tree Level 3, MaxLevel = 4
void testF()
{

  printf("\nStarting Test F\n\nLimit Tree: Non-Uniform Tree Level 3, MaxLevel = 4\n");
  maxTreeLevel = 4;

  // make the head node
  Node *head;
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  makeChildren( head );
  makeChildren( head->child[0]);
  makeChildren( head->child[1]);
  makeChildren( head->child[2]);
  makeChildren( head->child[3]);
  makeChildren( head->child[0]->child[0]);
  makeChildren( head->child[1]->child[2]);

  // grow the tree

  growTree(head);
  growTree(head);
  growTree(head);


  // print the tree for Gnuplot
  writeTree( head );

  //Destroys tree
  destroyTree(head);
}

// Creating a data-dependent quadtree
void testG()
{
  printf("\nStarting Test G\n\nCreating a data-dependent quadtree\n");
  maxTreeLevel = 100; // This caused about three hours of problems, I had the maxTreeLevel
                      // set to 5, so the program wouldn't run and would bottom out at the
                      // 5th level, and get stuck in a loop. I couldn't figure out why, but
                      // after a long sleep, I found out and now it works fine.
  // make the head node
  Node *head;
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  makeChildren( head );
  makeChildren( head->child[0]);
  makeChildren( head->child[1]);
  makeChildren( head->child[2]);
  makeChildren( head->child[3]);

  // Indicate the tree
  treeGenerator(head, 0.5, 0);

  // print the tree for Gnuplot
  writeTree( head );

  //Destroys tree
  destroyTree(head);
}

// Creating a data-dependent quadtree
void testH()
{
  printf("\nStarting Test G\n\nCreating a data-dependent quadtree Tolerance: 0.2 , Choice 1\n");
  maxTreeLevel = 100;
  // make the head node
  Node *head;
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  makeChildren( head );
  makeChildren( head->child[0]);
  makeChildren( head->child[1]);
  makeChildren( head->child[2]);
  makeChildren( head->child[3]);

  // Indicate the tree
  treeGenerator(head, 0.2 , 1);

  // print the tree for Gnuplot
  writeTree( head );

  //Destroys tree
  destroyTree(head);
}

// Creating a data-dependent quadtree
void testI()
{
  printf("\nStarting Test G\n\nCreating a data-dependent quadtree Tolerance: 0.1 , Choice 2\n");
  maxTreeLevel = 100;
  // make the head node
  Node *head;
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  makeChildren( head );
  makeChildren( head->child[0]);
  makeChildren( head->child[1]);
  makeChildren( head->child[2]);
  makeChildren( head->child[3]);

  // Indicate the tree
  treeGenerator(head, 0.1 , 2);

  // print the tree for Gnuplot
  writeTree( head );

  //Destroys tree
  destroyTree(head);
}
