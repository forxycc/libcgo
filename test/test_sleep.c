#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "co.h"

void	test(void *argv)
{
	int	v = (uintptr_t)argv;

	while(1)
	{
		co_print("test %ld sleep 3s......\n", v);
		co_nsleep(30000000);
		while(1)
		{
			uint64_t x = 0;

			x++;
			co_print("test %d\n", v);
		}
		co_print("test %ld sleep 3s ok.\n", v);
	}
}

int	main()
{
	int	i;

	co_init(1, 256, 1);

	for(i = 0; i < 16; i++)
	{
		co_go(test, (void *)(uintptr_t)i);
	}

	pause();

	return 0;
}
