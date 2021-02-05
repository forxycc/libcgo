#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "co.h"

typedef struct param_st
{
	char	*ip;
	int	port;
}param_t;

waitg_t wg;

void	tcp_client(void *argv)
{
	param_t	*dst = (param_t *)argv;
	char	buf[] = {"hello net!\n"};
	char	buf2[1024];
	int	i, ret,len = strlen(buf), len2 = 1024;
	void	*s;

	s = co_socket(SOCKET_TCP);
	assert(s != NULL);

	ret = co_connect(s, dst->ip, dst->port);
	assert(ret == 0);
	co_print("co_connect ok.\n");

	for(i = 0; i < 16; i++)
	{
		ret = co_send(s, buf, len);
		assert(ret > 0);
		co_print("co_send ok.\n");

		ret = co_recv(s, buf2, len2);
		if(ret < 0)
		{
			co_print("co_recv error.\n");
			break;
		}
		co_print("co_recv ok.\n");
		buf2[ret] = 0;
		printf("recv %s\n", buf2);
	}
	co_print("test over.\n");
	co_close(s);
	waitg_done(&wg);
}

int	main(int argc, char **argv)
{
	param_t dst;

	if(argc != 3)
	{
		printf("usage: client ip port.\n");
		return -1;
	}
	co_init(4, 256, 0);
	waitg_set(&wg, 1);

	dst.ip = argv[1];
	dst.port = atoi(argv[2]);
	co_go(tcp_client, &dst); 
	
	waitg_wait(&wg);

	return 0;
}
