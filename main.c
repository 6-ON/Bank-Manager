#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "libs/menu.h"

#define APP_NAME "BANK MANAGER"

#define REFRESH_DELAY 2

int main(char **args)
{
	accs = getData();
	
	while (true)
	{
		system(CLS);
		puts(APP_NAME);
		Menu();
		sleep(REFRESH_DELAY);
	}

	// printAccountlist(accs);

	return 0;
}
