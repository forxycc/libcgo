#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "co.h"

void	test(void *argv)
{
	int v = (uintptr_t)argv; 
	
	co_yield();

	printf("######### test %d ok.\n", v);
}

int	main()
{
	co_init(1, 256, 1);

	co_yield();

	co_go(test, (void *)1);
	

	while(1)
	{
		sleep(1000);
	}

	return 0;
}
