include ../CCONFIG

OPENSSL_PATH=/usr/local/openssl-debug-O0-noasm
CFLAGS += -g -O0
CFLAGS += -I../include
CFLAGS += -I$(OPENSSL_PATH)/include

LDFLAGS += -L../bin -lcgo 
LDFLAGS += $(OPENSSL_PATH)/lib/libcrypto.a -lpthread -ldl

all: test test_syscall test_sleep test_yield test_rwlock test_lock test_chan test_poll test_waitg testsm2

test: test.o
	$(CC) -o test test.o $(LDFLAGS) 

test_syscall: test_syscall.o
	$(CC) -o test_syscall test_syscall.o $(LDFLAGS)

test_sleep: test_sleep.o
	$(CC) -o test_sleep test_sleep.o $(LDFLAGS)

test_yield: test_yield.o
	$(CC) -o test_yield test_yield.o $(LDFLAGS) 

test_lock: test_lock.o
	$(CC) -o test_lock test_lock.o $(LDFLAGS) 

test_rwlock: test_rwlock.o
	$(CC) -o test_rwlock test_rwlock.o $(LDFLAGS) 

test_all: test_all.o
	$(CC) -o test_all test_all.o $(LDFLAGS) 

test_chan: test_chan.o
	$(CC) -o test_chan test_chan.o $(LDFLAGS) 

test_poll: test_poll.o
	$(CC) -o test_poll test_poll.o $(LDFLAGS) 

test_waitg: test_waitg.o
	$(CC) -o test_waitg test_waitg.o $(LDFLAGS) 

testsm2: testsm2.o asm.o
	$(CC) -o testsm2 testsm2.o asm.o $(LDFLAGS) 

testasm: testasm.o asm.o
	$(CC) -o testasm testasm.o asm.o $(LDFLAGS) 

asm.o: asm.S
	$(CC) -o asm.o asm.S -c

clean:
	rm -rf test test_syscall test_sleep test_yield test_lock test_rwlock test_all test_chan *.o
	rm -rf test_poll test_waitg testsm2 testasm
