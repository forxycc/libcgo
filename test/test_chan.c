#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include "co.h"

void	*chan;
uint64_t  unique = 0;

void	cwrite(void *argv)
{
	while(1)
	{
		co_print("writing %d ...\n", unique);
		co_chan_write(chan, (void *)&unique);
		co_print("writing %d ok.\n", unique);
		unique++;
	}
}

void	cread(void *argv)
{
	uint64_t v;

	while(1)
	{
		co_print("reading ....\n");
		co_chan_read(chan, &v);
		co_print("read %ld ok.\n", v);
	}
}

int	main()
{
	co_init(4, 256, 1);

	chan = co_chan_create(sizeof(uint64_t), 8);
	assert(chan != NULL);

	co_go(cwrite, (void *)1); 
	co_go(cwrite, (void *)2); 
	co_go(cread, (void *)1);
	co_go(cread, (void *)2);

	while(1)
	{
		sleep(1000);
	}

	return 0;
}
