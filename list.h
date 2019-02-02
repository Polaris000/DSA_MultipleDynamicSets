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

typedef struct ListofLists_
{
	List *lists_head;
	int size;
}ListofLists;


// global variables
int RAMINT[RAMSIZE];
ListofLists existinglists;
ListofLists freelist;

// methods
void display_freelist();