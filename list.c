#include <stdio.h>
#include <stdlib.h>
#include "list.h"


Node * create_new_node(int new_key)
{
	Node *new_node = malloc(sizeof(Node));
	new_node -> prev = -1;
	new_node -> next = -1;
	new_node -> key = new_key;

	return new_node;
}

List * create_new_list(int new_key)
{
	List *new_list = malloc(sizeof(List));
	Node *new_node = create_new_node(new_key);
	new_list -> id = ++NUMLISTS;
	new_list -> size = 1;
	new_list -> head = get_next_free_loc();
}


void display_lists()
{
	for (int i = 1; i <= NUMLISTS; i ++)
	{
		
	}
}
