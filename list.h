#include <stdio.h>
#include <stdlib.h>
#define RAMSIZE 20

extern int RAM[RAMSIZE];
extern int NUMLISTS;

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

// methods