#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// creating and inserting -----------------------------------------------
void insert_new_ele()
{
	int list_num, new_key;
	int free_space;

	printf("List you want to insert into: ");
	scanf("%d", &list_num);
	getchar();
	printf("Enter the key value: ");
	scanf("%d", &new_key);

	if (list_num > existinglists.size)
		{
			printf("FAILURE: LIST DOES NOT EXIST\n");
			return ;
		}
	if (list_num < 1)
		{
			printf("FAILURE: ENTER LIST NUMBER GREATER THAN 0\n");
			return ;
		}

	else
		{
			if((free_space = pop_from_freelist()) == -1)
			{
				printf("FAILURE: MEMORY NOT AVAILABLE\n");
				return ;
			}

			if(existinglists.lists_head[list_num - 1].head == -5)
			{
				existinglists.lists_head[list_num - 1].head = free_space;
				RAM[free_space - 1] = new_key;
				RAM[free_space + 1] = -1;
				return ;
			}

			existinglists.lists_head[list_num - 1].size ++;
			int current = existinglists.lists_head[list_num - 1].head;
			int prev = RAM[current + 1];

			if (new_key < RAM[current - 1])
			{
				existinglists.lists_head[list_num - 1].head = free_space;
				RAM[free_space - 1] = new_key;
				RAM[free_space] = current;
				RAM[free_space + 1] = -1;
				RAM[current + 1] = free_space;
				return ;
			}

			while(current != -1 && RAM[current - 1] <= new_key)
			{
				prev = current;
				current = RAM[current];
			}

			RAM[prev] = free_space;
			RAM[free_space] = current ;
			RAM[free_space - 1] = new_key;
			RAM[free_space + 1] = prev;

			printf("SUCCESS: ELEMENT ADDED\n");
		}

}

void create_new_list()
{

	if(underflow_check() == 1)
		printf("FAILURE: MEMORY NOT AVAILABLE \n");
	
	else
	{
		int free_space = pop_from_freelist();
		List new_list = existinglists.lists_head[existinglists.size - 1];
		new_list.head = free_space;
		new_list.size = 1;
		existinglists.size ++;
		new_list.id = existinglists.size;
		printf("The sequence number of the newly created list is: %d \n", new_list.id);
		printf("Enter key value to be inserted in the newly created list-%d: ", new_list.id);

		int new_key;
		scanf("%d", &new_key);
		getchar();
		existinglists.lists_head[existinglists.size - 1] = new_list;
		RAM[free_space] = -1;
		RAM[free_space - 1] = new_key;
		RAM[free_space + 1] = -1;
		printf("SUCCESS: NEW LIST CREATED\n");
	}
}

// --------------------------------------------------------------

// stack methods ------------------------------------------------

int get_tail_index()
{
	int start = freelist.lists_head[0].head;

	if (freelist.lists_head[0].size == 0)
		return -1;

	while(RAM[start] != -1)
	{
		start = RAM[start];
	}

	return start;
}

int get_second_last_index()
{
	int start = freelist.lists_head[0].head;

	if (freelist.lists_head[0].size < 2)
		return -1;

	int count = 0;
		while((RAM[RAM[start]] != -1) && (count <= freelist.lists_head[0].size))
		{
			start = RAM[start];
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
			RAM[index - 1] = nullval;
			RAM[index + 1] = nullval;
			RAM[index] = -1;
			freelist.lists_head[0].size ++;
			return 0;
		}

		RAM[start] = index;
		RAM[index - 1] = nullval;
		RAM[index + 1] = nullval;
		RAM[index] = -1;
		freelist.lists_head[0].size ++;

		return 0;
	}
}

int pop_from_freelist()
{

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
		int free_space = RAM[start];
		RAM[start] = -1;
		freelist.lists_head[0].size --;
		return free_space;
	}
}


int overflow_check()
{
	if (freelist.lists_head[0].size == RAMSIZE / 3)
		return 1;
	else
		return 0;
}

int underflow_check()
{
	// return 1  if size == 0
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
void delete_ele()
{
	int index, list_num, key;
	printf("List you want to delete from: ");
	scanf("%d", &list_num);
	getchar();
	printf("Enter the key value: ");
	scanf("%d", &key);

	if(list_num > existinglists.size)
	{
		printf("FAILURE: LIST DOES NOT EXIST\n");
		return ;
	}


	if ((index = get_element_with_key(list_num, key)) == -1 || existinglists.lists_head[list_num - 1].size == 0)
	{
		printf("FAILURE: ELEMENT DOES NOT EXIST OR LIST IS EMPTY\n");
		return ;
	}

	else
	{	
		// element at head of list and single element
		if (index == existinglists.lists_head[list_num - 1].head && existinglists.lists_head[list_num - 1].size == 1)
		{
			existinglists.lists_head[list_num - 1].head = -5;
			existinglists.lists_head[list_num - 1].size = 0;
			push_to_freelist(index);
			printf("SUCCESS: ELEMENT DELETED\n");
			return ;
		}

		//element at head
		if (index == existinglists.lists_head[list_num - 1].head && existinglists.lists_head[list_num - 1].size > 1)
		{
			existinglists.lists_head[list_num - 1].head = RAM[index];
			existinglists.lists_head[list_num - 1].size--;
			RAM[RAM[index] + 1] = -1;
			push_to_freelist(index);
			printf("SUCCESS: ELEMENT DELETED\n");
			return ;
		}

		// element at end
		else if (RAM[index] == -1)
		{
			int prev = RAM[index + 1];
			RAM[prev] = RAM[index];
			existinglists.lists_head[list_num - 1].size  --;
			push_to_freelist(index);
			printf("SUCCESS: ELEMENT DELETED\n");
			return ;
		}

		else
		{
			int prev = RAM[index + 1];
			RAM[prev] = RAM[index];
			RAM[RAM[index] + 1] = prev;
			existinglists.lists_head[list_num - 1].size  --;
			push_to_freelist(index);
			printf("SUCCESS: ELEMENT DELETED\n");
			return ;
		}
	}
}

// display all lists --------------------------------------------


void display_lists()
{
	if(existinglists.size == 0)
	{
		printf("FAILURE: THERE ARE NO LISTS\n");
		return ;
	}

	for(int i = 1; i <= existinglists.size; i ++)
	{
		int tmp = existinglists.lists_head[i - 1].head;
		printf("Elements of list-%d are: \n", i);
		printf("key \t next \t prev \n");

		while(tmp != -1 && tmp != -5)
		{
			int print_var;
			printf("%d \t ", RAM[tmp - 1]);
			print_var = RAM[tmp] != -1 ? printf("%d \t", RAM[tmp]) : printf("NIL \t");
			print_var = RAM[tmp + 1] != -1 ? printf("%d \n", RAM[tmp + 1]) : printf("NIL \n");
			tmp = *(RAM + tmp);
		}
	}
}

void display_freelist()
{
	int index = freelist.lists_head[0].head;
	printf("[");
	while (index != -1)
	{
		printf("%d  ", index);
		index = RAM[index];
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
	if (list_num > existinglists.size)
	{
		printf("FAILURE: LIST DOES NOT EXIST\n");
		return ;
	}

	if (list_num < 1)
	{
		printf("FAILURE: ENTER VALUE GREATER THAN 0\n");
		return ;
	}

	int count = existinglists.lists_head[list_num - 1].size;
	printf("Total number of nodes in list %d are %d.\n", list_num, count);
}

// searching ----------------------------------------------------
int get_element_with_key(int list_num, int key)
{
	List required_list = existinglists.lists_head[list_num - 1];

	int index = required_list.head;
	while (index != -1 && index != -5)
	{
		if (RAM[index - 1] == key)
			return index;

		index = RAM[index];
	}

	return -1;
}
// --------------------------------------------------------------