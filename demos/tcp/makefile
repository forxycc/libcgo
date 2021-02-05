include ../../CCONFIG

CFLAGS += -g -O0
CFLAGS += -I../../include

LDFLAGS += -L../../bin -lcgo

all: test_tcp_server test_tcp_client 

test_tcp_server: test_tcp_server.o
	$(CC) -o test_tcp_server test_tcp_server.o $(LDFLAGS) 
	cp -rf test_tcp_server ../../bin/

test_tcp_client: test_tcp_client.o
	$(CC) -o test_tcp_client test_tcp_client.o $(LDFLAGS) 
	cp -rf test_tcp_client ../../bin/

clean:
	rm -rf test_tcp_server test_tcp_client  *.o
	rm -rf ../../bin/test_tcp_server
	rm -rf ../../bin/test_tcp_client
