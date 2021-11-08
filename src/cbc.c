/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   cbc.c                                                                    */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/08 07:16:05 by yhetman                                  */
/*   Updated: 2021/11/08 07:16:07 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */


#include "aes.h"


void
cbc_encrypting(uint8_t *input, uint8_t *key, uint8_t input_legth)
{
	t_aes 	cbc_aes;
	uint8_t	*IV,
			amount_blocks,
			counter = 0,
			i;
	long 	j;

	amount_blocks = input_legth / 16;

	init_t_aes(&cbc_aes, key, NULL);

	IV = (uint8_t*) malloc(sizeof(uint8_t) * cbc_aes.N_k * 4);
	IV = (uint8_t*)random_string((char*)IV, cbc_aes.N_k * 4);

	add_round_key(input, IV, 0);
	encrypt_block(&cbc_aes, input);

	for (i = 1; i < amount_blocks; i++)
	{
		add_round_key( &input[i * 16],  &input[(i - 1) * 16], 0);
		encrypt_block(&cbc_aes, &input[i * 16]);
	}
	for (j = input_legth - cbc_aes.N_k * 4; j < input_legth; j++, counter++)
		input[j] = IV[counter];

	free(cbc_aes.w);
}

void
cbc_decrypting(uint8_t *input, uint8_t *key, uint8_t input_legth)
{
	t_aes 	cbc_aes;
	uint8_t	*IV,
			amount_blocks,
			counter = 0;
	long 	i,
			j;

	amount_blocks = input_legth / 16;

	init_t_aes(&cbc_aes, key, NULL);

	IV = (uint8_t*) malloc(sizeof(uint8_t) * cbc_aes.N_k * 4);
	
	for (j = input_legth - 2 * 16; j < input_legth - 16; j++, counter++)
		IV[counter] = input[j];
	
	
	for (i = amount_blocks - 2; i > 0; i--)
	{
		decrypt_block(&cbc_aes, &input[i * 16]);
		add_round_key(&input[i * 16],  &input[(i - 1) * 16], 0);
	}

	decrypt_block(&cbc_aes, input);
	add_round_key(input,  IV, 0);
	add_round_key(&input[input_legth - 2 * 16], &input[input_legth - 2 * 16], 0);
	free(cbc_aes.w);
}