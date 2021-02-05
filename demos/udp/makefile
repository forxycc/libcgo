include ../../CCONFIG

CFLAGS += -g -O0
CFLAGS += -I../../include

LDFLAGS += -L../../bin -lcgo

all: test_udp_server test_udp_client 

test_udp_server: test_udp_server.o
	$(CC) -o test_udp_server test_udp_server.o $(LDFLAGS) 
	cp -rf test_udp_server ../../bin/

test_udp_client: test_udp_client.o
	$(CC) -o test_udp_client test_udp_client.o $(LDFLAGS) 
	cp -rf test_udp_client ../../bin/

clean:
	rm -rf test_udp_server test_udp_client  *.o
	rm -rf ../../bin/test_udp_server
	rm -rf ../../bin/test_udp_client
