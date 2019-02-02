#include <stdio.h>
#include <stdlib.h>
#define RAMSIZE 15

//structs

typedef struct List_
{
	int head;
	int size;
	int id;
}List;

typedef struct ListofLists_
{
	List *lists_head;
	int size;
}ListofLists;


// global variables
int RAMINT[RAMSIZE];
ListofLists existinglists;
ListofLists freelist;

// methods
void display_freelist();
void display_lists();
int get_element_with_key(int list_num, int key);
int count_total_ele();
int count_ele_list(int list_num);
int delete_ele(int list_num, int key);
int underflow_check();
int overflow_check();
int pop_from_freelist();
int push_to_freelist(int index);
int get_second_last_index();
int get_tail_index();
int create_new_list(int new_key);
int insert_new_ele(int list_num, int new_key);