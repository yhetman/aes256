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
inverse_sub_bytes(uint8_t *state)
{
	uint8_t	i,
			j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			state[4 * i + j] = inverse_s_box[state[4 * i + j]];
}


static void
inverse_shift_rows(uint8_t *state)
{

	uint8_t i,
			j,
			k,
			temp;

	for (i = 1; i < 4; i++)
	{
		for (k = 0; k < i; k++)
		{
			temp = state[4 * i + 4 -1];
			for (j = 4 - 1; j > 0; j--)
				state[4 * i + j] = state[4 * i + j - 1];
			state[4 * i + 0] = temp;
		}
	}
}

void
decrypt_block(t_aes *aes, uint8_t *state)
{
	uint8_t round;
	uint8_t	c[4] = {
		0x0e, 0x09, 0x0d, 0x0b
	};

	add_round_key(state, aes->w, aes->N_r);

	for (round = aes->N_r - 1; round >= 1; round--)
	{
		inverse_shift_rows(state);
		inverse_sub_bytes(state);
		add_round_key(state, aes->w, round);
		mix_columns(state, c);
	}

	inverse_shift_rows(state);
	inverse_sub_bytes(state);
	add_round_key(state, aes->w, 0);
}


void
decipher(t_aes *aes)
{
	uint8_t state[4 * 4],
			i,
			j;

	
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			state[4 * i + j] = aes->cipher_text[i + 4 * j];


	decrypt_block(aes, state);
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			aes->decipher_text[i + 4 * j] = state[4 * i + j];
}
