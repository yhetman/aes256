/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ecb.c                                                                    */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/08 01:31:22 by yhetman                                  */
/*   Updated: 2021/11/08 01:31:24 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */


#include "aes.h"


void
ecb_encrypting(uint8_t *input, uint8_t*key, size_t input_legth)
{
	t_aes 	ecb_aes;
	uint8_t	amount_blocks,
			i;
	amount_blocks = input_legth / 16;
	init_t_aes(&ecb_aes, key, NULL);
	for (i = 0; i < amount_blocks; i++)
		encrypt_block(&ecb_aes, &input[i * 16]);
	free(ecb_aes.w);	
}

void
ecb_decrypting(uint8_t *input, uint8_t*key, size_t input_legth)
{
	t_aes 	ecb_aes;
	uint8_t	amount_blocks,
			i;

	amount_blocks = input_legth / 16;
	init_t_aes(&ecb_aes, key, NULL);
	for (i = 0; i < amount_blocks; i++)
		decrypt_block(&ecb_aes, &input[i * 16]);
	free(ecb_aes.w);
}