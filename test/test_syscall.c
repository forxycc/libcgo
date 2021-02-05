#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "co.h"

void	test(void *argv)
{
	int v = (uintptr_t)argv; 

	while(1)
	{
		co_print("test %d co_enter_syscall ...\n", v);
		co_enter_syscall();
		co_print("test %d co_enter_syscall over.\n", v);

		usleep(10000);

		co_print("test %d co_exit_syscall ...\n", v);
		co_exit_syscall();
		co_print("test %d co_exit_syscall over.\n", v);
	}
}

int	main()
{

	co_init(2, 8, 1);

	co_go(test, 0); 
	co_go(test, (void *)1); 
	co_go(test, (void *)2); 

	while(1)
	{
		sleep(1000);
	}

	return 0;
}

