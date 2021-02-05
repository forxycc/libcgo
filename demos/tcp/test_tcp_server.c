#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "co.h"

waitg_t wg;

void	server_echo(void *argv)
{
	int	ret;
	char	buf[1024];
	void	*conn = argv;

	co_print("start server_echo ...\n");
	while(1)
	{
		ret = co_recv(conn, buf, 1024);
		if(ret > 0)
		{
			buf[ret] = 0;
			co_print("co recv: %s\n", buf);

			ret = co_send(conn, buf, ret);
			if(ret < 0)
			{
				printf("co_send failed.\n");
				break;
			}

		}
		else if(ret <= 0)
		{
			break;
		}
	}
	co_print("server_echo done.\n");
	co_close(conn);
}

void	tcp_server(void *argv)
{
	int	ret, port = (uintptr_t)argv;
	void	*ln, *s;

	ln = co_socket(SOCKET_TCP);
	ret = co_listen(ln, "0.0.0.0", port);
	assert(ret == 0);
	while(1)
	{
		s = co_accept(ln);
		assert(s != NULL);
		co_print("accept ok.\n");

		co_go(server_echo, s);
	}
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

	co_go(tcp_server, (void *)(uintptr_t)port); 

	waitg_wait(&wg);
	return 0;
}
