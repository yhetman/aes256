/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   cfb.c                                                                    */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/08 11:10:18 by yhetman                                  */
/*   Updated: 2021/11/08 11:10:20 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

void
cfb_encrypting(uint8_t *input, uint8_t *key, size_t input_legth)
{
	t_aes 	cfb_aes;
	uint8_t	*IV,
			*auxIV,
			counter = 0;
	int 	amount_blocks,
			i,
			j;


	amount_blocks = input_legth / 16;

	init_t_aes(&cfb_aes, key, NULL);

	auxIV = (uint8_t*) malloc(sizeof(uint8_t) * cfb_aes.N_k * 4);
	IV = (uint8_t*) malloc(sizeof(uint8_t) * cfb_aes.N_k * 4);
	IV = (uint8_t*)random_string((char*)IV, cfb_aes.N_k * 4);
	
	memcpy(auxIV, IV, cfb_aes.N_k * 4);

	encrypt_block(&cfb_aes, IV);

	for (i = 0; i < amount_blocks - 1; i++)
	{
		add_round_key(&input[i * 16],  IV, 0);
		encrypt_block(&cfb_aes, &input[i * 16]);
	}
	for (j = input_legth - 16; j < (int)input_legth; j++, counter++)
		input[j] = auxIV[counter];

	free(IV);
	free(auxIV);
	free(cfb_aes.w);
}

void
cfb_decrypting(uint8_t *input, uint8_t *key, size_t input_legth)
{
	t_aes 	cfb_aes;
	uint8_t	*IV,
			counter = 0;
	int 	amount_blocks,
			i,
			j;


	amount_blocks = input_legth / 16;

	init_t_aes(&cfb_aes, key, NULL);

	IV = (uint8_t*) malloc(sizeof(uint8_t) * cfb_aes.N_k * 4);
	
	for (j = input_legth -  16; j < (int)input_legth; j++, counter++)
		IV[counter] = input[j];
	
	encrypt_block(&cfb_aes, IV);

	for (i = 0; i < amount_blocks - 1; i++)
	{
		add_round_key(&input[i * 16],  IV, 0);
		encrypt_block(&cfb_aes, &input[i * 16]);
	}

	add_round_key(&input[input_legth - 16], &input[input_legth - 16], 0);
	
	free(IV);
	free(cfb_aes.w);
}