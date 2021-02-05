#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include "co.h"

uint64_t	count = 0;
void		*lock;

void	test1(void *argv)
{
	int	who = (uintptr_t)argv;

	while(1)
	{
		co_lock(lock);
		count++;
		/* lock ok, we can use prinf */
		co_print("[test %d]: %ld\n", who, count); 
		//usleep(1000);
		co_unlock(lock);
		/* NOTE: if no call co_yield, will get lock right now ! */
		co_yield();
	}
}

void	test2(void *argv)
{
	while(1)
	{
		co_lock(lock);
		count++;
		/* lock ok, we can use prinf */
		printf("test2: %ld\n", count); 
		co_unlock(lock);
		/* NOTE: if no call co_yield, will get lock right now ! */
		//co_yield();
	}
}

void	test3(void *argv)
{
	while(1)
	{
		co_lock(lock);
		count++;
		/* lock ok, we can use prinf */
		printf("test3: %ld\n", count); 
		usleep(1000);
		co_unlock(lock);
		/* NOTE: if no call co_yield, will get lock right now ! */
		//co_yield();
	}
}

int main()
{
	int	i;

	co_init(4, 256, 1); 

	lock = co_lock_create();

	for(i = 0; i < 16; i++)
	{
		co_go(test1, (void *)(uintptr_t)i); 
	}
	pause();

	return 0;
}
