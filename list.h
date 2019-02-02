#include <stdio.h>
#include <stdlib.h>
#define RAMSIZE 15

//structs

typedef struct List_
{
	int head;
	int size;
	int id;
}List;


// global variables
int RAMINT[RAMSIZE];
extern List existinglists[RAMSIZE / 3];
extern int NUMLISTS;

// methods