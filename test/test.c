#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "co.h"

void	test(void *argv)
{
	int v = (uintptr_t)argv; 

	while(1)
	{
		printf("######### test %d ok.\n", v);
		usleep(100000);
	}
}

int	main()
{
	int i;

	co_init(4, 256, 1);

	for(i = 0;i < 16; i++)
	{
		co_go(test, (void *)(uintptr_t)i);
	}

	pause();
	return 0;
}
