#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rc4.h"

#ifdef DEBUG_SBOX
static void dbg_print_sbox(RC4_t *s, int bpr)
{
	int i;
	for(i=0; i<SBOXSIZE; i++) {
		printf("%02X", s->SBOX[i]);
		if(((i+1)%bpr) == 0) { printf("\n"); } else { printf(" "); }
	}
	printf("\n");
}
#endif

RC4_t* new_rc4_state(uint8_t *iv, uint32_t ivlen, uint8_t *key, uint32_t keylen)
{
	RC4_t *s;
	int i, j, kb;
	uint8_t KBOX[1024];

	// Error Checking
	kb = ivlen + keylen;
	if(kb > sizeof(KBOX)) { fprintf(stderr, "Key Bytes Too Large!\n"); return NULL; }

	// Initialize the SBOX
	s = (RC4_t *)malloc( sizeof(RC4_t) );
	for(i=0; i<SBOXSIZE; i++) { s->SBOX[i] = i; }

	// Load the KBOX
	if(ivlen > 0) { memcpy(&KBOX[0], iv, ivlen); }
	memcpy(&KBOX[ivlen], key, keylen);

	j=0; // KSA
	for(i=0; i<SBOXSIZE; i++) {
		j = (j + s->SBOX[i] + KBOX[i % kb]) % SBOXSIZE;
		xorSwap(s->SBOX[i], s->SBOX[j]);
	}

	return s;
}

int rc4_crypt(RC4_t *s, uint8_t *data, uint32_t data_len, uint8_t *out, uint32_t print_keystream)
{
	int n=0, i=0, j=0;

	// Loop over each byte in the plaintext string
	for(n=0; n<data_len; n++) {
		i = (i+1) % SBOXSIZE;
		j = (j + s->SBOX[i]) % SBOXSIZE;
		xorSwap(s->SBOX[i], s->SBOX[j]);
		out[n] = s->SBOX[ (s->SBOX[i] + s->SBOX[j]) % SBOXSIZE ];

		if(print_keystream) {
			printf("%02X", out[n]);
		}

		// {En,De}cryption operation
		out[n] ^= data[n];
	}

	return n;
}

void del_rc4_state(RC4_t *state)
{
	free(state);
}
