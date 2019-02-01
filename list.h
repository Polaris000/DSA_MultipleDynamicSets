#include <stdio.h>
#include <stdlib.h>
#define RAMSIZE 20

//structs
typedef struct Node_
{
	int key;
	int next;
	int prev;
}Node;

typedef struct List_
{
	int head;
	int size;
	int id;
}List;


// global variables
extern int RAMINT[RAMSIZE];
extern List RAMLIST[RAMSIZE / 3];
extern int NUMLISTS;

// methods