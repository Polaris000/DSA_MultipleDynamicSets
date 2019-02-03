#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// creating and inserting -----------------------------------------------
void insert_new_ele(int list_num, int new_key)
{


	if(get_element_with_key(list_num, new_key) != -1)
		return -1;

	else
	{
		printf("inside else for insert_new_ele #\n");

		int free_space;
		if((free_space = pop_from_freelist()) == -1)
				return -2; 
		existinglists.lists_head[list_num - 1].size ++;
		int current = existinglists.lists_head[list_num - 1].head;
		int prev = RAMINT[current + 1];

		printf("insert current and prev at start %d %d\n", current, prev);

		if (new_key < RAMINT[current - 1])
		{
			printf("insert if new key < current #\n");
			existinglists.lists_head[list_num - 1].head = free_space;
			RAMINT[free_space - 1] = new_key;
			RAMINT[free_space] = current;
			RAMINT[free_space + 1] = -1;
			RAMINT[current + 1] = free_space;
			return 0;
		}

		while(current != -1 && RAMINT[current - 1] <= new_key)
		{
			printf("insert current and prev in loop %d %d\n", current, prev);
			prev = current;
			current = RAMINT[current];
		}

		printf("inside else for insert_new_ele ###\n");
		RAMINT[prev] = free_space;
		RAMINT[free_space] = current ;
		RAMINT[free_space - 1] = new_key;
		RAMINT[free_space + 1] = prev;
		

		return 0;
	}
}

void create_new_list()
{
	if(overflow_check())
		printf("FAILURE: MEMORY NOT AVAILABLE \n");
	else
	{
		int free_space = pop_from_freelist();
		List new_list = existinglists.lists_head[existinglists.size - 1];
		new_list.head = free_space;
		//printf("free space: %d", free_space);
		new_list.size = 1;
		new_list.id = ++existinglists.size;
		printf("The sequence number of the newly created list is: %d \n", new_list.id);
		printf("Enter key value to be inserted in the newly created list-%d: ");

		int new_key;
		scanf("%d", &new_key);
		getchar();
		existinglists.lists_head[existinglists.size - 1] = new_list;
		RAMINT[free_space] = -1;
		RAMINT[free_space - 1] = new_key;
		RAMINT[free_space + 1] = -1;
		// printf("list id: %d \n", new_list.id);
		// printf("%d \t %d \t %d \n", RAMINT[free_space - 1], RAMINT[free_space], RAMINT[free_space + 1]);
		printf("SUCCESS\n");
	}
}

// --------------------------------------------------------------

// stack methods ------------------------------------------------

int get_tail_index()
{
	int start = freelist.lists_head[0].head;

	if (freelist.lists_head[0].size == 0)
	{
		return -1;
	}

	while(RAMINT[start] != -1)
	{
		start = RAMINT[start];
	}

	return start;
}

int get_second_last_index()
{
	printf("inside second last index\n");
	int start = freelist.lists_head[0].head;
	printf("start %d \n", start);

	if (freelist.lists_head[0].size < 2)
		return -1;

	int count = 0;
		while((RAMINT[RAMINT[start]] != -1) && (count <= freelist.lists_head[0].size))
		{
			start = RAMINT[start];
			count ++;
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
		if (start == -1)
		{
			freelist.lists_head[0].head = index;
			RAMINT[index - 1] = -2;
			RAMINT[index + 1] = -2;
			RAMINT[index] = -1;\
			freelist.lists_head[0].size ++;
			return 0;
		}

		RAMINT[start] = index;
		RAMINT[index - 1] = -2;
		RAMINT[index + 1] = -2;
		RAMINT[index] = -1;
		freelist.lists_head[0].size ++;

		return 0;
	}
}

int pop_from_freelist()
{

	printf("INside pop from freelist\n");
	int underflow_return = underflow_check();

	if(underflow_return == 1)
		return -1;

	else if (underflow_return == 2)
	{
		freelist.lists_head[0].size --;
		int free_space = freelist.lists_head[0].head;
		freelist.lists_head[0].head = -1;
		return free_space;
	}

	else
	{
		int start = get_second_last_index();
		printf("second last %d\n", start);
		int free_space = RAMINT[start];
		RAMINT[start] = -1;
		freelist.lists_head[0].size --;
		printf("free space %d \n", free_space);

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
	//return 1  if size == 0
	// return 0 if size > 1
	// return 2 if size == 1

	if (freelist.lists_head[0].size == 0)
		return 1;
	else if(freelist.lists_head[0].size == 1)
		return 2;
	else
		return 0;
}

// --------------------------------------------------------------

// Delete element --------------------------------------------------
int delete_ele(int list_num, int key)
{
	int index;
	printf("inside del\n");
	if ((index = get_element_with_key(list_num, key)) == -1 || existinglists.lists_head[list_num - 1].size == 0)
		return -1;
	else
	{

		if (index == existinglists.lists_head[list_num - 1].head)
		{
			printf("inside if of del \n");
			existinglists.lists_head[list_num - 1].head = RAMINT[index];
			RAMINT[RAMINT[index] + 1] = -1;
			push_to_freelist(index);
			return 0;
		}

		printf("inside del index is %d:\n", index);
		int prev = RAMINT[index + 1];
		RAMINT[prev] = RAMINT[index];
		RAMINT[RAMINT[index] + 1] = prev;
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
			printf("%d \n", *(RAMINT + tmp + 1));
			 // printf("tmp in display lists : %d\n", tmp);
			tmp = *(RAMINT + tmp);
		}
	}
}

void display_freelist()
{
	int index = freelist.lists_head[0].head;
	printf("[");
	while (index != -1)
	{
		printf("%d, ", index);
		index = RAMINT[index];
	}
	printf("]\n");
}
// --------------------------------------------------------------


// count all elements
void count_total_ele()
{
	int count = 0;
	for(int i = 1; i <= existinglists.size; i ++)
		count += existinglists.lists_head[i - 1].size;

	printf("Total number of nodes in all lists are %d.\n", count);
}

void count_ele_list()
{
	int list_num;
	printf("Enter the list number: ");
	scanf("%d", &list_num);
	int count = existinglists.lists_head[list_num - 1].size;
	printf("Total number of nodes in list %d are %d.\n", list_num, count);
}
// --------------------------------------------------------------

// searching ----------------------------------------------------
int get_element_with_key(int list_num, int key)
{
	List required_list = existinglists.lists_head[list_num - 1];

	int index = required_list.head;
	printf("%d \n ", index);
	//printf("inside get ele #\n");

	while (index != -1)
	{
		 // printf("inside get ele ##\n");
		if (RAMINT[index - 1] == key)
			return index;
		//printf("%d \n ", index);
		index = RAMINT[index];
	}

	return -1;
}
// --------------------------------------------------------------