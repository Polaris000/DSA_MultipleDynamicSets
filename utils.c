#include <stdio.h>
#include <stdlib.h>
#include "list.h"


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
}

// void swap_elements(int index1, int freenode)
// {
// 	int free_next = RAMINT[freenode];
// 	RAMINT[freenode - 1] = RAMINT[index1 - 1];
// 	RAMINT[freenode] = RAMINT[index1];
// 	RAMINT[freenode + 1] = RAMINT[index1 + 1];
// 	RAMINT[index1 - 1] = -2;
// 	RAMINT[index1] = free_next;
// 	RAMINT[index1 + 1] = -2;
// }

// int is_freelist_contiguous()
// {
// 	int index = freelist.lists_head[0].head;
// 	while (index != -1)
// 	{
// 		printf("%d, ", index);
// 		// index = RAMINT[index];
// 		if (index + 3 == RAMINT[index])
// 			index += 3;
// 		else
// 			return index;
// 	}

// 	return 1;
// }

// int perform_defragmentation()
// {
// 	int index;
// 	if (index = is_freelist_contiguous())
// 	{
// 		printf("Defrag not required...\n");
// 		return -1;
// 	}

// 	else
// 	{
// 		int head = freelist.lists_head[0].head;
// 		swap_elements(index);


// 	}
// }

//
// Create a new list
// 2. Insert a new node in a given list in sorted order: Here list and node object is taken as input
// 3. Delete an element from a given list: Here list and node object is taken as input
// 4. Count total elements excluding free list
// 5. Count total elements of a list: Here list is taken as input
// 6. Display all lists
// 7. Display free list
// 8. Perform defragmentation


// void create_new_list_menu()
// {
// 	printf("The sequence number of the newly created list is: %d", cre
// 	Enter key value to be inserted in the newly created list-n: here user inputs integer m
// }

// int select_pref_option()
// {
// 	printf("Your option: \n");
// 	int option;

// 	scanf("%d", &option);

// 	switch(option)
// 	{
// 		case 0:
// 			return -1;
// 		case 1: create_new_list_menu(); break;
// 		case 2: insert_new_ele()
// 	}

// }


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
	RAMINT[i - 1] = -2;
	if (i == RAMSIZE - 2)
		RAMINT[i] = -1;
	else
		RAMINT[i] = i + 3;
	RAMINT[i + 1] = -2;
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



void disp_ram()
{
	for (int i = 1; i <= RAMSIZE; i ++)
		printf("%d (%d) |", RAMINT[i - 1], i);

	printf(" \t ***\n");

;

	printf(" \t ***\n");
}



void main()
{
	init_all();
	create_new_list(3);
	
	insert_new_ele(1, 4);
	// display_freelist();
	// display_lists();
	// disp_ram();

	insert_new_ele(1, 2);
	// display_freelist();
	// display_lists();
	// disp_ram();

	insert_new_ele(1, 5);
	//insert_new_ele(1, 8);
	display_freelist();
	display_lists();
	disp_ram();

	delete_ele(1, 5);
	display_freelist();
	display_lists();
	disp_ram();

	printf("%d", count_total_ele());
	printf("%d", count_ele_list(1));


}

