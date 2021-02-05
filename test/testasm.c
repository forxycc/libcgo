#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "co.h"
#include "waitg.h"
#include "atomic.h"

waitg_t wg;

int	count = 0;

extern void teststack();

void	test(void *argv)
{
	int	ret, n = 0;
	uint64_t who = (uint64_t)argv;
	unsigned char out[256],in[256];
	size_t	outlen = 256, inlen;

	while(1)
	{
		teststack();
		/*
		n = atomic_inc(&count);
		if((n & 0xff) == 0)
		{
			co_print("%ld enc ok, count = %d\n", who, n);
		}
		*/
	}
	waitg_done(&wg);
}

int	main()
{
	int	ret, i;

	co_init(4, 256, 1);

	waitg_set(&wg, 1);
	for(i = 0; i < 32; i++)
	{
		co_go(test, (void *)(uintptr_t)i);
	}

	waitg_wait(&wg);

	return 0;
}
