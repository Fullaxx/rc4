#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rc4.h"

typedef struct rc4_input_output {
	unsigned char iv[512];
	unsigned char key[512];
	unsigned char pt[512];
	unsigned char ct[512];
	unsigned char dec[512];
} rc4_io_t;

void print_hex(uint8_t *buf, uint32_t len)
{
	int i;
	for(i=0; i<len; i++) { printf("%02X", buf[i]); }
}

void run_test_vectors(rc4_io_t *tv)
{
	RC4_t *s;
	size_t keylen = strlen((char *)tv->key);
	size_t ptlen = strlen((char *)tv->pt);

	printf("%s ", (char *)tv->key);
	s = new_rc4_state(tv->iv, 0, tv->key, keylen);
	(void) rc4_crypt(s, tv->pt, ptlen, tv->ct, 1);
	printf(" %s ", (char *)tv->pt);
	print_hex(tv->ct, ptlen);
	del_rc4_state(s);

	s = new_rc4_state(tv->iv, 0, tv->key, strlen((char *)tv->key));
	(void) rc4_crypt(s, tv->ct, strlen((char *)tv->pt), tv->dec, 0);
	printf(" %s ", (char *)tv->dec);
	printf("\n");
	del_rc4_state(s);
}

int main(int argc, char *argv[])
{
	rc4_io_t tv;

	memset(&tv, 0, sizeof(tv));
	strcpy((char *)tv.key, "Key");
	strcpy((char *)tv.pt, "Plaintext");
	run_test_vectors(&tv);

	memset(&tv, 0, sizeof(tv));
	strcpy((char *)tv.key, "Wiki");
	strcpy((char *)tv.pt, "pedia");
	run_test_vectors(&tv);

	memset(&tv, 0, sizeof(tv));
	strcpy((char *)tv.key, "Secret");
	strcpy((char *)tv.pt, "Attack at down");
	run_test_vectors(&tv);
}
