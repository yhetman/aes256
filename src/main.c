/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/09/24 15:35:50 by yhetman                                  */
/*   Updated: 2021/10/03 00:52:52 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

static uint8_t*
allocate_w(t_aes *aes)
{
	uint8_t *w;

	switch (sizeof(aes->key))
	{
		default :
		case 16 :
			aes->N_k = 4;
			aes->N_r = 10;
			break;
		case 24 :
			aes->N_k = 6;
			aes->N_r = 12;
			break;
		case 32 :
			aes->N_k = 8;
			aes->N_r = 14;
			break;
	}

	w = (uint8_t *)malloc(sizeof(uint8_t) * aes->N_b * (aes->N_r + 1) * 4);
	return (w);
}

static void
init_t_aes(t_aes *aes, uint8_t *key, uint8_t *input)
{
	aes->N_b = 4;
	aes->key = key;
	aes->input = input;
	aes->w = allocate_w(aes);

	init_key_scheduler(aes);
}


static void
print_uint8_t(uint8_t *str)
{
	uint8_t i;

	for (i = 0; i < 4; i++)
		printf("%02x %02x %02x %02x ", str[4 * i + 0], str[4 * i + 1], str[4 * i + 2], str[4 * i + 3]);
	printf("\n");
}


int
main()
{
	t_aes 	aes;

	uint8_t initial_key[] = {
		0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b,
		0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13,
		0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b,
		0x1c, 0x1d, 0x1e, 0x1f};

	uint8_t input[] = {
		0x00, 0x11, 0x22, 0x33,
		0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xaa, 0xbb,
		0xcc, 0xdd, 0xee, 0xff};

	printf("Plaintext:\n");
	print_uint8_t(input);

	
	init_t_aes(&aes, initial_key, input);

	cipher(&aes);
	
	printf("Ciphered text:\n");
	print_uint8_t(aes.cipher_text);
	
	decipher(&aes);

	printf("Deciphered text:\n");
	print_uint8_t(aes.decipher_text);

	free(aes.w);

	return 0;
}
