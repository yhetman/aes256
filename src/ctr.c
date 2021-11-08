/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ctr.c                                                                    */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/08 10:46:08 by yhetman                                  */
/*   Updated: 2021/11/08 10:46:10 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

void
ctr(uint8_t *input, uint8_t *key, size_t input_legth)
{
	t_aes 	ctr_aes;
	uint8_t	*nonce,
			*_nonce;
	size_t	blocks,
			i,
			j;

	blocks = input_legth / 16;

	init_t_aes(&ctr_aes, key, NULL);

	nonce = (uint8_t*) malloc(sizeof(uint8_t) * ctr_aes.N_k * 4);
	_nonce = (uint8_t*) malloc(sizeof(uint8_t) * ctr_aes.N_k * 4);
	
	nonce = (uint8_t*)random_string((char*)nonce, ctr_aes.N_k * 4);

	for (i = 0; i < blocks; i++)
	{
		memcpy(_nonce, nonce, ctr_aes.N_k * 4);
		encrypt_block(&ctr_aes, _nonce);
		add_round_key( &input[i * 16], _nonce, 0);
		for (j = 0; j < ctr_aes.N_k * 4; j++)
			nonce[j]++;
	}
	free(nonce);
	free(_nonce);
	free(ctr_aes.w);	
}
