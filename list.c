#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// creating and inserting -----------------------------------------------
int insert_new_ele(int list_num, int new_key)
{
	if(get_element_with_key(list_num, new_key) != -1)
		return -1;
	else
	{
		int free_space;
		existinglists.lists_head[list_num - 1].size ++;
		if((free_space = pop_from_freelist()) == -1)
			return -2;

		int prev = existinglists.lists_head[list_num - 1].head;
		int current = RAMINT[prev];

		if (new_key < current)
		{
			existinglists.lists_head[list_num - 1].head = free_space;
			RAMINT[free_space - 1] = new_key;
			RAMINT[free_space] = prev;
			RAMINT[free_space + 1] = -1;
			return 0;
		}

		while(RAMINT[current] != -1)
		{
			if(RAMINT[current - 1] > new_key)
			{
				RAMINT[prev] = free_space;
				RAMINT[free_space] = current ;
				return 0;
			}

			current += 3;
			prev += 3;
		}

		RAMINT[current] = free_space;

		return 0;

	}
}

int create_new_list(int new_key)
{
	// existinglists[size - 1].head = *******;
	// new_list -> id = ++existinglists.size;
	// new_list -> size = 1;
	// new_list -> head = get_next_free_loc(); 
	// existinglists[new_list -> id] = new_list;

	if(overflow_check())
		return -1;
	else
	{
		int free_space = pop_from_freelist();
		List new_list = existinglists.lists_head[existinglists.size - 1];
		new_list.head = free_space;
		new_list.size = 1;
		new_list.id = ++existinglists.size;
		RAMINT[free_space] = -1;
		RAMINT[free_space - 1] = new_key;
		RAMINT[free_space + 1] = -1;

		return 0;	
	}
}

// --------------------------------------------------------------

// stack methods ------------------------------------------------

int get_tail_index()
{
	int start = freelist.lists_head[0].head;

		while(RAMINT[start] != -1)
		{
			start += 3;
		}

	return start;
}

int get_second_last_index()
{
	int start = freelist.lists_head[0].head;

		while(RAMINT[RAMINT[start]] != -1)
		{
			start += 3;
		}

	return start;
}

int push_to_freelist(int index)
{
	if(overflow_check())
		return -1;
	else
	{
		int start = get_tail_index();
		RAMINT[start] = index;
		RAMINT[index - 1] = -2;
		RAMINT[index + 1] = -2;
		freelist.lists_head[0].size ++;
		return 0;
	}
}

int pop_from_freelist()
{
	if(underflow_check())
		return -1;

	else
	{
		int start = get_second_last_index();
		int free_space = RAMINT[start];
		RAMINT[start] = -1;
		freelist.lists_head[0].size --;
		return free_space;
	}
}

int overflow_check()
{
	if (freelist.lists_head[0].size == RAMSIZE)
		return 1;
	else
		return 0;
}

int underflow_check()
{
	if (freelist.lists_head[0].size == 0)
		return 1;
	else
		return 0;
}

// --------------------------------------------------------------

// Delete element --------------------------------------------------
int delete_ele(int list_num, int key)
{
	int index;
	if ((index = get_element_with_key(list_num, key)) == -1 || existinglists.lists_head[list_num - 1].size == 0)
		return -1;
	else
	{
		int prev = RAMINT[index + 1];
		RAMINT[prev] = RAMINT[index];
		existinglists.lists_head[list_num - 1].size --;
		push_to_freelist(index);
		return 0;
	}

}

// display all lists --------------------------------------------
void display_lists()
{

	if(existinglists.size == 0)
		printf("Nothing here!\n");

	for(int i = 1; i <= existinglists.size; i ++)
	{
		int tmp = existinglists.lists_head[i - 1].head;
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

void display_freelist()
{
	int index = freelist.lists_head[0].head;
	printf("[");
	while (RAMINT[index] != -1)
	{
		printf("%d, ", RAMINT[index]);
		index += 3;
	}
	printf("]\n");
}
// --------------------------------------------------------------


// count all elements
int count_total_ele()
{
	int count = 0;
	for(int i = 1; i <= existinglists.size; i ++)
		count += existinglists.lists_head[i - 1].size;

	return count;
}

int count_ele_list(int list_num)
{
	return existinglists.lists_head[list_num - 1].size;
}
// --------------------------------------------------------------

// searching ----------------------------------------------------
int get_element_with_key(int list_num, int key)
{
	List required_list = existinglists.lists_head[list_num - 1];

	int index = required_list.head;

	while (RAMINT[index - 1] != -1)
	{
		if (RAMINT[index - 1] == key)
			return index;
	}

	return -1;
}
// --------------------------------------------------------------