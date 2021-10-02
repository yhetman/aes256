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
#include "gfield.h"

void	multiply_c(uint8_t *c, uint8_t *bytes, uint8_t *result)
{
	result[0] = multiplication_table[256 * c[0] + bytes[0]]^multiplication_table[256 * c[3] + bytes[1]]^multiplication_table[256 * c[2] + bytes[2]]^multiplication_table[256 * c[1] + bytes[3]]; 
	result[1] = multiplication_table[256 * c[1] + bytes[0]]^multiplication_table[256 * c[0] + bytes[1]]^multiplication_table[256 * c[3] + bytes[2]]^multiplication_table[256 * c[2] + bytes[3]]; 
	result[2] = multiplication_table[256 * c[2] + bytes[0]]^multiplication_table[256 * c[1] + bytes[1]]^multiplication_table[256 * c[0] + bytes[2]]^multiplication_table[256 * c[3] + bytes[3]]; 
	result[3] = multiplication_table[256 * c[3] + bytes[0]]^multiplication_table[256 * c[2] + bytes[1]]^multiplication_table[256 * c[1] + bytes[2]]^multiplication_table[256 * c[0] + bytes[3]];

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

		// multiply_c(c, column, result);

		for (i = 0; i < 4; i++)
			state[N_b * i + j] = result[i];
	}
}


void 		cipher(t_aes *aes) //uint8_t *in, uint8_t *out, uint8_t *w)
{
	uint8_t	state[4 * aes->N_b];
	uint8_t round,
			i,
			j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < aes->N_b; j++)
			state[aes->N_b * i + j] = aes->input[i + 4 * j];


	//add_round_key(state, aes->w, 0);

	for (round = 1; round < aes->N_r; round++)
	{
		sub_bytes(state, aes->N_b);
//		shift_rows(state);
		mix_columns(state, aes->N_b);
//		add_round_key(state, aes->w, round);
	}

	sub_bytes(state, aes->N_b);
//	shift_rows(state);
//	add_round_key(state, aes->w, aes->N_r);

	for (i = 0; i < 4; i++)
		for (j = 0; j < aes->N_b; j++)
			aes->cipher_text[i + 4 * j] = state[aes->N_b * i + j];
}