#include "asserttrue.h"
#include <stdio.h>

int asserttrue(int assertion, int printCheck)
{
	if (assertion == 1)
	{
		if (printCheck == 1)
		{ 
			printf("PASSED\n");
		}
		return 0;
	}
	else
	{
		if (printCheck == 1)
		{
			printf("FAILED\n");
		}
		return 1;
	}
}
