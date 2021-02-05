#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "co.h"

waitg_t wg;

void	udp_server(void *argv)
{
	int	ret, port = (uintptr_t)argv;
	char	buf[1024];
	void	*s;

	s = co_socket(SOCKET_UDP);
	assert(s != NULL);

	ret = co_listen(s, "0.0.0.0", port);
	assert(ret == 0);

	while(1)
	{
		addr_t addr;
		ret = co_recvfrom(s, buf, 1024, &addr);
		if(ret > 0)
		{
			co_print("recvfrom ok.\n");

			ret = co_sendto(s, buf, ret, &addr);
			if(ret < 0)
			{
				printf("co_recv failed.\n");
				break;
			}
			co_print("sendto ok.\n");

		}
		else if(ret < 0)
		{
			printf("co_recv failed.\n");
			break;
		}
	}
	co_close(s);
	waitg_done(&wg);
}

int	main(int argc, char **argv)
{
	int	port;

	if(argc != 2)
	{
		printf("usage: server port.\n");
		return -1;
	}
	port = atoi(argv[1]);
	co_init(4, 256, 1);
	waitg_set(&wg, 1);

	co_go(udp_server, (void *)(uintptr_t)port); 

	waitg_wait(&wg);
	return 0;
}
