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
	 // disp_ram();
}

void disp_ram()
{
	for (int i = 1; i <= RAMSIZE; i ++)
		printf("%d (%d) |", RAMINT[i - 1], i);

	printf(" \t ***\n");
}


void swap(int i, int j, int list_num)
{
	int next = RAMINT[i];
	int prev = RAMINT[i + 1];

	if (next == -1 && prev == -1)
	{
		existinglists.lists_head[list_num - 1].head = j;
		RAMINT[j + 1] = prev;
		RAMINT[j - 1] = RAMINT[i - 1];
		RAMINT[j] = next;
		RAMINT[i - 1] = nullval;
	}

	// filled node at end of list
	if (next == -1)
	{
		RAMINT[j] = next;
		RAMINT[j + 1] = prev;
		RAMINT[j - 1] = RAMINT[i - 1];
		RAMINT[RAMINT[j + 1]] = j;

		RAMINT[i - 1] = nullval; 
	}

	// filled node at head of list
	else if(prev == -1)
	{
		existinglists.lists_head[list_num].head = j;
		RAMINT[j + 1] = prev;
		RAMINT[j - 1] = RAMINT[i - 1];
		RAMINT[RAMINT[next] + 1] = j;
		RAMINT[i - 1] = nullval;
	}


	// in the middle
	else
	{
		RAMINT[RAMINT[i + 1]] = j;
		RAMINT[RAMINT[next] + 1] = j;
		RAMINT[i - 1] = nullval;
	}

}


void reset_order()
{
	freelist.lists_head[0].head = 1;
	printf("size: %d\n", freelist.lists_head[0].size);
	int count = 1;
	int i = 1;
	RAMINT[i] = -1;
	RAMINT[i - 1] = nullval;
	RAMINT[i + 1] = nullval;
	while(count < freelist.lists_head[0].size)
	{
		printf(" in loop: i %d count %d\n", i, count);
		RAMINT[i] = i + 3;
		RAMINT[i - 1] = nullval;
		RAMINT[i + 1] = nullval;
		i += 3;
		count ++;
	}

	RAMINT[i] = -1;


}

int getlistnum(int i)
{
	for(int i = 1; i < existinglists.size; i++)
	{
		if (existinglists.lists_head[i - 1].head == i)
			return i;
	}
}

void get_together(int i)
{
	int j;
	int list_num;
	for(j = RAMSIZE - 2; j >= 1; j -= 3)
	{
		if(RAMINT[j - 1] == nullval)
			break;
	}
	if (j <= i)
	{
		return ;
	}

	list_num = getlistnum(i);

	printf("%d %d %d\n", i , j, list_num);
	swap(i, j, list_num);
	reset_order();
}




void perform_defragmentation()
{
	int index = 0;

	if(freelist.lists_head[0].size == 0)
		printf("Nothing free!\n");

	else
	{
		int index = freelist.lists_head[0].head;	
		int size = freelist.lists_head[0].size;
		int i;

		for (i = 1; i <= RAMSIZE; i += 3)
		{
			if (RAMINT[i - 1] != nullval)
				break;
		}

		if (i == 3 * size + 1)
		{
			printf("INside if defrag\n");
			reset_order();
		}

		else
		{
			printf("INside else defrag\n");
			get_together(i);
		}

	}


}

void select_pref_option()
{
	
	int option;

	do
	{
		printf("Select an option between 0 and 8: ");
		scanf("%d", &option);
		getchar();
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

	printf(" ****************** \n");

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
	RAMINT[i - 1] = nullval;
	if (i == RAMSIZE - 2)
		RAMINT[i] = -1;
	else
		RAMINT[i] = i + 3;
	RAMINT[i + 1] = nullval;
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


// void main()
// {
// 	init_all();
// 	create_new_list(2);
// 	insert_new_ele(1, 3);
// 	display_freelist();
// 	// display_lists();
// 	disp_ram();
// 	insert_new_ele(1, 4);
// 	display_freelist();
// 	// display_lists();
// 	disp_ram();
// 	insert_new_ele(1, 5);
// 	display_freelist();
// 	disp_ram();
// 	insert_new_ele(1, 7);
// 	display_freelist();
// 	display_lists();
// 	disp_ram();

// 	delete_ele(1, 5);
// 	display_freelist();
// 	display_lists();
// 	disp_ram();

// 	perform_defragmentation();
// 	disp_ram();
// 	display_freelist();
// 	display_lists();
// 	printf("%d", count_total_ele());
// 	printf("%d", count_ele_list(1));


// }

