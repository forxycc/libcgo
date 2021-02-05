#ifndef ATOMIC_H
#define	ATOMIC_H

static inline void atomic_store(int *ptr, int v)
{
	__sync_lock_test_and_set(ptr, v);
}

static inline int atomic_load(int *ptr)
{
	return __sync_fetch_and_add(ptr, 0); 
}

static inline void atomic_cas(int *ptr, int oldv, int newv)
{
	while(!__sync_bool_compare_and_swap(ptr, oldv, newv));
}

static inline int atomic_add(int *ptr, int v)
{
	return __sync_fetch_and_add(ptr, v);
}

static inline int atomic_sub(int *ptr, int v)
{
	return __sync_fetch_and_sub(ptr, v);
}

static inline int atomic_inc(int *ptr)
{
	return __sync_fetch_and_add(ptr, 1);
}

static inline int atomic_dec(int *ptr)
{
	return __sync_fetch_and_sub(ptr, 1);
}
	
#endif

