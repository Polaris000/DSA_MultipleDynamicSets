#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


void display_menu()
{
	printf("Select an option:  \n"
	"1. Create a new list  \n"
	"2. Insert a new element in a given list in sorted order   \n"
	"3. Delete an element from a given list   \n"
	"4. Count total elements excluding free list  \n"
	"5. Count total elements of a list  \n"
	"6. Display all lists  \n"
	"7. Display free list  \n"
	"8. Perform defragmentation  \n"
	"9. Press 0 to exit  \n");

	printf(" ****************** \n");
	disp_ram();
}


void disp_ram()
{
	for (int i = 1; i <= RAMSIZE; i ++)
		printf("%d (%d) |", RAM[i - 1], i);

	printf(" \t ***\n");
}


void swap(int i, int j, int list_num)
{
	int next = RAM[i];
	int prev = RAM[i + 1];

	if (next == -1 && prev == -1)
	{
		existinglists.lists_head[list_num - 1].head = j;
		RAM[j + 1] = prev;
		RAM[j - 1] = RAM[i - 1];
		RAM[j] = next;
		RAM[i - 1] = nullval;
		RAM[i + 1] = nullval;
	}

	// filled node at end of list
	else if (next == -1)
	{
		RAM[j] = next;
		RAM[j + 1] = prev;
		RAM[j - 1] = RAM[i - 1];
		RAM[RAM[j + 1]] = j;

		RAM[i - 1] = nullval; 
	}

	// filled node at head of list
	else if(prev == -1)
	{
		existinglists.lists_head[list_num].head = j;
		RAM[j + 1] = prev;
		RAM[j - 1] = RAM[i - 1];
		RAM[RAM[next] + 1] = j;
		RAM[i - 1] = nullval;
	}

	// in the middle
	else
	{
		RAM[RAM[i + 1]] = j;
		RAM[RAM[next] + 1] = j;
		RAM[i - 1] = nullval;
	}
}

void reset_order()
{
	freelist.lists_head[0].head = 1;
	printf("size: %d\n", freelist.lists_head[0].size);
	int count = 1;
	int i = 1;
	RAM[i] = -1;
	RAM[i - 1] = nullval;
	RAM[i + 1] = nullval;
	while(count < freelist.lists_head[0].size)
	{
		printf(" in loop: i %d count %d\n", i, count);
		RAM[i] = i + 3;
		RAM[i - 1] = nullval;
		RAM[i + 1] = nullval;
		i += 3;
		count ++;
	}

	RAM[i] = -1;
}

int getlistnum(int i)
{
	for(int i = 1; i < existinglists.size; i++)
	{
		if (existinglists.lists_head[i - 1].head == i)
			return i;
	}
}

void get_together()
{

	int index = freelist.lists_head[0].head;	
	int size = freelist.lists_head[0].size;
	int i;

	for (i = 1; i <= RAMSIZE; i += 3)
	{
		if (RAM[i - 1] != nullval)
			break;
	}

	if (i == 3 * size + 1)
	{
		printf("INside if defrag\n");
		return ;
	}

	else
	{
		printf("INside else defrag\n");
	}


	int j;
	int list_num;

	for(j = RAMSIZE - 2; j >= 1; j -= 3)
	{
		if(RAM[j - 1] == nullval)
			break;
	}
	if (j <= i)
	{
		return ;
	}

	list_num = getlistnum(i);

	printf("%d %d %d\n", i , j, list_num);
	swap(i, j, list_num);
	get_together();
}

void perform_defragmentation()
{
	int index = 0;

	if(freelist.lists_head[0].size == 0)
		printf("Nothing free!\n");

	else
	{
		get_together();
		reset_order();
	}
}

void select_pref_option()
{
	int option = 0;
	do
	{
		printf("Select an integer between 0 and 8: ");
		scanf("%d", &option);
		getchar();
		printf(" \n");
	} while (option < 0 || option > 8);

	switch(option)
	{
		case 1: create_new_list(); 			break; //done
		case 2: insert_new_ele();			break; //done
		case 3: delete_ele();				break; //done
		case 4:	count_total_ele();			break; //done
		case 5: count_ele_list();  			break; //done
		case 6: display_lists();     		break; //done
		case 7: display_freelist(); 		break; //done
		case 8: perform_defragmentation(); 	break; //done
		case 0: exit(0); 					break; //done
	}

	printf(" \n"); printf(" \t ****************** \n"); printf(" \n");
}


void init_freelist()
{
	freelist.lists_head = malloc(sizeof(List));
	freelist.size = 1;
	freelist.lists_head[0].head = 1;
	freelist.lists_head[0].size = RAMSIZE / 3;
	freelist.lists_head[0].id = 0;
}

void init_existinglists()
{
	existinglists.lists_head = malloc(sizeof(List) * RAMSIZE / 3);
	existinglists.size = 0;
}


void fill_contig_loc(int i)
{
	RAM[i - 1] = nullval;
	if (i == RAMSIZE - 2)
		RAM[i] = -1;
	else
		RAM[i] = i + 3;
	RAM[i + 1] = nullval;
}

void set_up_ram_int()
{
	for(int i = 1; i <= RAMSIZE; i += 3)
		fill_contig_loc(i);
}

void init_all()
{
	init_freelist();
	init_existinglists();
	set_up_ram_int();
}


