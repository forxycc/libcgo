#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include "co.h"
#include "atomic.h"

extern int sm2_encrypt(const EC_KEY *key, const EVP_MD *digest, 
		const uint8_t *msg, size_t msg_len, uint8_t *ciphertext_buf, size_t *ciphertext_len); 

EC_KEY *eckey = NULL;

waitg_t wg;

int	count = 0;

void	test(void *argv)
{
	int	ret, n = 0;
	uint64_t who = (uint64_t)argv;
	unsigned char out[256],in[256];
	size_t	outlen = 256, inlen;

	memset(in, 0x31, 256);
	inlen = 32;

	while(1)
	{
		ret = sm2_encrypt(eckey, EVP_sm3(), in, inlen, out, &outlen);
		assert(ret == 1);

		n = atomic_inc(&count);
		if((n & 0xff) == 0)
		{
			co_print("%ld enc ok, count = %d\n", who, n);
		}
	}
	waitg_done(&wg);
}

int	main()
{
	int	ret, i;

	eckey = EC_KEY_new_by_curve_name(NID_sm2);
	assert(eckey != NULL);

	ret = EC_KEY_generate_key(eckey);
	assert(ret == 1);

	co_init(4, 256, 1);

	waitg_set(&wg, 1);
	for(i = 0; i < 32; i++)
	{
		co_go(test, (void *)(uintptr_t)i);
	}

	waitg_wait(&wg);

	return 0;
}
