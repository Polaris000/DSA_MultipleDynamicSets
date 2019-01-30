#include <stdio.h>

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

void main()
{
	display_menu();
}

