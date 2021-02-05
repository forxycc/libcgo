#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include "co.h"
#include "lcl.h"

uint64_t count =  0;
co_lock_t *lock;

void	test(void *argv)
{
	int	v = (uintptr_t)argv; 
//	void	*bp = NULL, *sp = NULL;

	while(1)
	{
		/*
		co_print("######### test %d ...\n", v);
		__asm__ __volatile__ ("mov %%rbp, %0;" : "=m"(bp) : : "memory");
		__asm__ __volatile__ ("mov %%rsp, %0;" : "=m"(sp) : : "memory");

		co_print("######## test stack check: %p, %p, %p, %p.\n", currentm->stack, currentm->co_current->stack, sp, bp);
		assert(sp <= bp); 
		assert(sp >= currentm->co_current->stack);
		*/
		
		co_print("######### test %d co_enter_syscall ....\n", v); 
		co_enter_syscall();
		co_print("######### test %d co_enter_syscall over.\n", v); 

		usleep(1);

		co_print("######### test %d co_exit_syscall .....\n", v); 
		co_exit_syscall();
		co_print("######### test %d co_exit_syscall over.\n", v); 

		/*
		co_print("######### test %d sleep ....\n",v );
		co_nsleep(100000);
		co_print("######### test %d sleep ok.\n",v );
		*/

	}
}

int	main()
{
	co_init(1, 256, 1);

	lock = co_lock_create();

	co_go(test, (void *)1);
	co_go(test, (void *)2);
	co_go(test, (void *)3);
	co_go(test, (void *)4);

	while(1)
	{
		sleep(1000);
	}

	return 0;
}
