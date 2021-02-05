#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include "co.h"

uint64_t	count = 0;
void		*lock;

void	read1(void *argv)
{
	while(1)
	{
		co_rwlock_rlock(lock);
		co_print("read1: %ld\n", count);
		co_rwlock_unlock(lock);
		co_yield();
	}
}

void	read2(void *argv)
{
	while(1)
	{
		co_rwlock_rlock(lock);
		co_print("read2: %ld\n", count);
		co_rwlock_unlock(lock);
		co_yield();
	}
}

void	write1(void *argv)
{
	while(1)
	{
		co_rwlock_wrlock(lock);
		count++;
		co_print("write1++ = %ld\n", count);
		co_rwlock_unlock(lock);
		co_yield();
	}
}

void	write2(void *argv)
{
	while(1)
	{
		co_rwlock_wrlock(lock);
		count++;
		co_print("write2++ = %ld\n", count);
		co_rwlock_unlock(lock);
		co_yield();
	}
}

int main()
{
	co_init(2, 256, 1); 

	lock = co_rwlock_create();
	co_go(read1, NULL); 
	co_go(read2, NULL); 
	co_go(write1, NULL); 
	co_go(write2, NULL); 

	pause();
	co_print("main exit.\n");
	return 0;
}
