/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ofb.c                                                                    */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/08 10:28:56 by yhetman                                  */
/*   Updated: 2021/11/08 10:29:00 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"


void
ofb_encrypting(uint8_t *input, uint8_t *key, size_t input_legth)
{
	t_aes 	ofb_aes;
	uint8_t	*IV,
			*auxIV,
			counter = 0;
	int 	i,
			amount_blocks,
			j;

	amount_blocks = input_legth / 16;

	init_t_aes(&ofb_aes, key, NULL);

	auxIV = (uint8_t*) malloc(sizeof(uint8_t) * ofb_aes.N_k * 4);
	IV = (uint8_t*) malloc(sizeof(uint8_t) * ofb_aes.N_k * 4);
	IV = (uint8_t*)random_string((char*)IV, ofb_aes.N_k * 4);
	
	memcpy(auxIV, IV, ofb_aes.N_k * 4);

	encrypt_block(&ofb_aes, IV);

	for (i = 0; i < amount_blocks - 1; i++)
	{
		add_round_key(&input[i * 16],  IV, 0);
		encrypt_block(&ofb_aes, IV);
	}
	
	for (j = input_legth - 16; j < (int)input_legth; j++, counter++)
		input[j] = auxIV[counter];

	free(IV);
	free(auxIV);
	free(ofb_aes.w);
}

void
ofb_decrypting(uint8_t *input, uint8_t *key, size_t input_legth)
{
	t_aes 	ofb_aes;
	uint8_t	*IV,
			counter = 0;
	int 	amount_blocks,
			i,
			j;

	amount_blocks = input_legth / 16;

	init_t_aes(&ofb_aes, key, NULL);

	IV = (uint8_t*) malloc(sizeof(uint8_t) * ofb_aes.N_k * 4);
	
	for (j = input_legth -  16; j < (int)input_legth; j++, counter++)
		IV[counter] = input[j];
	
	encrypt_block(&ofb_aes, IV);

	for (i = 0; i < amount_blocks - 1; i++)
	{	
		add_round_key(&input[i * 16],  IV, 0);
		encrypt_block(&ofb_aes, IV);
	}

	add_round_key(&input[input_legth - 16], &input[input_legth - 16], 0);
	
	free(IV);
	free(ofb_aes.w);
}