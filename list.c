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
	existinglists[new_list -> id] = *new_list;
}


void display_lists()
{
	for(int i = 1; i <= NUMLISTS; i ++)
	{
		int tmp = existinglists[i - 1].head;
		printf("Elements of list-%d are: \n", i);
		printf("key \t next \t prev \n");
		while(tmp != -1)
		{
			printf("%d \t ", *(RAMINT + tmp - 1));
			printf("%d \t ", *(RAMINT + tmp));
			printf("%d \n ", *(RAMINT + tmp + 1));

			tmp = *(RAMINT + tmp);
		}
	}

}

int count_total_ele()
{
	int count = 0;
	for(int i = 1; i <= NUMLISTS; i ++)
		count += existinglists[i - 1].size;

	return count;
}

int count_ele_list(int list_num)
{
	return existinglists[list_num - 1].size;
}