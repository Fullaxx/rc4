#ifndef __RC4_H__
#define __RC4_H__

#include <stdint.h>

#define xorSwap(x,y) { if((x) != (y)) { (x) ^= (y) ^= (x) ^= (y); } }

#define SBOXSIZE (256)
typedef struct rc4_state {
	uint8_t SBOX[SBOXSIZE];
} RC4_t;

RC4_t* new_rc4_state(uint8_t *iv, uint32_t ivlen, uint8_t *key, uint32_t keylen);
int rc4_crypt(RC4_t *s, uint8_t *data, uint32_t data_len, uint8_t *out, uint32_t print_keystream);
void del_rc4_state(RC4_t *state);

#endif	/*	__RC4_H__	*/
