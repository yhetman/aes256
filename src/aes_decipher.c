/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   aes_decipher.c                                                           */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 13:51:29 by yhetman                                  */
/*   Updated: 2021/10/02 23:16:40 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

static void
inverse_sub_bytes(uint8_t *state, int N_b)
{
	uint8_t	i,
			j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < N_b; j++)
			state[N_b * i + j] = inverse_s_box[state[N_b * i + j]];
}


static void
inverse_shift_rows(uint8_t *state, int N_b)
{

	uint8_t i,
			j,
			k,
			temp;

	for (i = 1; i < 4; i++)
	{
		for (k = 0; k < i; k++)
		{
			temp = state[N_b * i + N_b -1];
			for (j = N_b - 1; j > 0; j--)
				state[N_b * i + j] = state[N_b * i + j - 1];
			state[N_b * i + 0] = temp;
		}
	}
}


void
decipher(t_aes *aes)
{
	uint8_t state[4 * aes->N_b],
			round,
			i,
			j;

	uint8_t	c[4] = {
		0x0e, 0x09, 0x0d, 0x0b
	};
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < aes->N_b; j++)
			state[aes->N_b * i + j] = aes->cipher_text[i + 4 * j];


	add_round_key(state, aes->w, aes->N_r, aes->N_b);

	for (round = aes->N_r - 1; round >= 1; round--)
	{
		inverse_shift_rows(state, aes->N_b);
		inverse_sub_bytes(state, aes->N_b);
		add_round_key(state, aes->w, round, aes->N_b);
		mix_columns(state, aes->N_b, c);
	}

	inverse_shift_rows(state, aes->N_b);
	inverse_sub_bytes(state, aes->N_b);
	add_round_key(state, aes->w, 0, aes->N_b);

	for (i = 0; i < 4; i++)
		for (j = 0; j < aes->N_b; j++)
			aes->decipher_text[i + 4 * j] = state[aes->N_b * i + j];
}
