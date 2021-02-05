#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include "co.h"

void	*chan;

int	start = 0;

void	cwrite(void *argv)
{
	uint64_t	v = 0;

	while(1)
	{
		if(start != 1)
		{
			co_yield();
			continue;
		}
		co_print("######## write %ld.....\n", v);
		co_chan_write(chan, &v);
		co_print("######## write %ld ok.\n", v);
		v++;
	}
}

void	cread(void *argv)
{
	int	i,num,ret;
	uint64_t v = 0; 
	void	*pl;
	event_t e, out[16], *cur;

	co_print("########### creading...\n");

	pl = co_poll_create(8);
	assert(pl != NULL);

	e.chan = chan;
	e.event = EVENT_READ; 
	co_poll_ctl(pl, POLL_CTL_ADD, &e);

	start = 1;

retry:
	num = co_poll(pl, out, 512); 
	for(i = 0; i < num; i++)
	{
		cur = &out[i];
		if(cur->event & EVENT_READ)
		{
			ret = co_chan_read(cur->chan, &v); 
			/* NOTE: mayby failed. */
			assert(ret == 0);
			co_print("######### read ok, v = %d\n", v);
		}
		if(cur->event & EVENT_WRITE )
		{
			co_print("#### event has write\n"); 
			v = 3;
			ret = co_chan_write(cur->chan, (void *)&v); 
			/* NOTE: mayby failed. */
			assert(ret == 0);
		}
	}
	//co_yield();
	goto retry;
}

int	main()
{
	co_init(2, 256, 1);

	chan = co_chan_create(sizeof(uint64_t), 1);
	assert(chan != NULL);

	co_go(cwrite, NULL);
	co_go(cread, NULL);

	while(1)
	{
		sleep(1000);
	}
	return 0;
}
