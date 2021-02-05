#ifndef CO_H
#define	CO_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define	SOCKET_TCP	(1)
#define	SOCKET_UDP	(2)

#define	POLL_CTL_ADD	(1)
#define	POLL_CTL_DEL	(2)
#define	POLL_CTL_MOD	(3)
#define	EVENT_READ	(1<<0)
#define	EVENT_WRITE	(1<<1)

typedef	void (* cgofunc)(void *argv);
typedef struct addr_st addr_t;
typedef struct event_st event_t;
typedef struct waitg_st waitg_t;

struct waitg_st
{
	int	value;
	void	*co;
};

struct  addr_st
{
	struct	sockaddr addr;
	int	len;
};

struct event_st
{
	void 	*chan;
	int	event;
};

void co_init(int nprocessor, int max_co_per_processor, int enable_preempt);
void co_go(cgofunc function, void *argv);
void co_nsleep(uint64_t nseconds);
void co_yield();
void co_enter_syscall();
void co_exit_syscall();
void co_print(const char *format, ...);
void co_dispreempt(int disable);

void waitg_set();
void waitg_done();
void waitg_wait();

uint64_t co_nanotime();

void *co_lock_create();
void co_lock(void *lock);
void co_unlock(void *lock);
void co_lock_destory(void *lock);

void *co_rwlock_create();
void co_rwlock_rlock(void *rwlock);
void co_rwlock_wrlock(void *rwlock);
void co_rwlock_unlock(void *rwlock);
void co_rwlock_destory(void *rwlock);

void *co_chan_create(int typesize, int qlen);
int co_chan_read(void *chan, void *addr);
int co_chan_write(void *chan, void *addr);

void *co_poll_create(int sz);
int co_poll_ctl(void *pl, int ctl, event_t *e); 
int co_poll(void *pl, event_t *out, int sz);

void *co_socket(int type);
int co_listen(void *s, char *ip, int port);
void *co_accept(void *s);
int co_connect(void *s, char *ip, int port);
int co_send(void *s, void *buf, int len);
int co_sendto(void *s, void *buf, int len, addr_t *addr);
int co_recv(void *s, void *buf, int len);
int co_recvfrom(void *s, void *buf, int len, addr_t *addr);
void co_close(void *s);

#endif

