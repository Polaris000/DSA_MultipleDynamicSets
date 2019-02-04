#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


int main()
{
	init_all();
	while(1)
	{
		display_menu();
		select_pref_option();
	}

	return 0;
}
