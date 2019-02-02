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

//
// Create a new list
// 2. Insert a new node in a given list in sorted order: Here list and node object is taken as input
// 3. Delete an element from a given list: Here list and node object is taken as input
// 4. Count total elements excluding free list
// 5. Count total elements of a list: Here list is taken as input
// 6. Display all lists
// 7. Display free list
// 8. Preform defragmentation

// int select_pref_option()
// {
// 	printf("Your option: \n");
// 	int option;

// 	scanf("%d", &option);

// 	switch(option)
// 	{
// 		case 0:
// 			return -1;
// 		case 1: create_new_list(); break;
// 		case 2: insert
// 	}

// }

// populate ramint with lists
// void set_up_ram_int()
// {
// 	for(int i = 1; i <= RAMSIZE; i += 3)
// 	{
// 		fill_contig_loc(i);
// 	}
// }


// void fill_contig_loc(int i)
// {
// 	RAMINT[i + 0] = RAMLIST[i].key;
// 	RAMINT[i + 1] = RAMLIST[i].next;
// 	RAMINT[i + 2] = RAMLIST[i].prev;
// }

void disp_ram()
{
	for (int i = 1; i <= RAMSIZE; i ++)
		printf("|%d|", RAMINT[i - 1]);

}



void main()
{
	display_menu();
	disp_ram();
}

