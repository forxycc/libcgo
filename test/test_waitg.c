#include "co.h"

waitg_t	wg;
waitg_t	wg2;

void	done1(void *argv)
{
	co_nsleep(1000000000);
	waitg_done(&wg2);
	co_print("done1 ok.\n");
}

void	done2(void *argv)
{
	co_nsleep(1000000000);
	waitg_done(&wg2);
	co_print("done2 ok.\n");
}

void	test(void *argv)
{
	co_print("test...\n");

	waitg_set(&wg2, 2);
	co_go(done1, 0);
	co_go(done2, 0);
	waitg_wait(&wg2);
	co_print("wg2 over.\n");

	co_nsleep(1000000000);
	waitg_done(&wg);
	co_print("test over.\n");
}

int	main()
{
	co_init(4, 256, 0);

	waitg_set(&wg, 1);
	co_go(test, 0);
	waitg_wait(&wg);

	co_print("main exit.\n");
	return 0;
}
