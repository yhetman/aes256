/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   aes_cipher.c                                                             */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 13:29:02 by yhetman                                  */
/*   Updated: 2021/10/02 13:29:04 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"


uint8_t		*allocate_w(t_aes *aes)
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


t_aes		init_t_aes(uint8_t *key, uint8_t *input)
{
	t_aes 	data;

	data = (t_aes)malloc(sizeof(s_aes));
	data.N_b = 4;
	data.key = key;
	data.state = input;
	data.w = allocate_w(&data);
	init_key_scheduler(&data);
	return (data);
}


void	multiply_c(uint8_t *c, uint8_t *bytes, uint8_t * result)
{
	result[0] = multiplication(c[0], bytes[0]) ^ multiplication(c[3], bytes[1]) ^ multiplication(c[2], bytes[2]) ^ multiplication(c[1], bytes[3]); 
	result[1] = multiplication(c[1], bytes[0]) ^ multiplication(c[0], bytes[1]) ^ multiplication(c[3], bytes[2]) ^ multiplication(c[2], bytes[3]); 
	result[2] = multiplication(c[2], bytes[0]) ^ multiplication(c[1], bytes[1]) ^ multiplication(c[0], bytes[2]) ^ multiplication(c[3], bytes[3]); 
	result[3] = multiplication(c[3], bytes[0]) ^ multiplication(c[2], bytes[1]) ^ multiplication(c[1], bytes[2]) ^ multiplication(c[0], bytes[3]);

}


void	sub_bytes(uint8_t *state, int N_b)
{

	uint8_t	i,
			j;
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < N_b; j++)
			state[N_b * i + j] = s_box[state[N_b * i + j]];
}


void	mix_columns(uint8_t *state, int N_b)
{

	uint8_t	c[4] =									//
					{								//	Coefficients of Polynomial
						0x02, 0x01, 0x01, 0x03		//
					};								//

	uint8_t i,
			j,
			column[4],
			result[4];

	for (j = 0; j < N_b; j++)
	{
		for (i = 0; i < 4; i++)
			column[i] = state[N_b * i + j];

		multiply_c(c, column, result);

		for (i = 0; i < 4; i++)
			state[N_b * i + j] = result[i];
	}
}