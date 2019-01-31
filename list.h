#include <stdio.h>
#include <stdlib.h>

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
}List;

// methods