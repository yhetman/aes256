/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   aes_cipher.c                                                             */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 13:29:02 by yhetman                                  */
/*   Updated: 2021/10/02 23:53:57 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

static void
sub_bytes(uint8_t *state)
{

	uint8_t	i,
			j;
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			state[4 * i + j] = s_box[state[4 * i + j]];
}


static void
shift_rows(uint8_t *state)
{

	uint8_t	i,
			j,
			k,
			temp;

	for (i = 1; i < 4; i++)
	{
		for (k = 0; k < i; k++)
		{
			temp = state[4 * i + 0];
			
			for (j = 1; j < 4 ;  j++)
				state[4 * i + j - 1] = state[4 * i + j];

			state[4 * i + 4 - 1] = temp;
		}
	}
}


void
encrypt_block(t_aes *aes, uint8_t *state)
{
	uint8_t round;
	uint8_t c[4] = {
		0x02, 0x01, 0x01, 0x03
	};
	

	add_round_key(state, aes->w, 0);

	for (round = 1; round < aes->N_r; round++)
	{
		sub_bytes(state);
		shift_rows(state);
		mix_columns(state, c);
		add_round_key(state, aes->w, round);
	}

	sub_bytes(state);
	shift_rows(state);
	add_round_key(state, aes->w, aes->N_r);
}

void
cipher(t_aes *aes)
{
	uint8_t	state[16],
			i,
			j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			state[4 * i + j] = aes->input[i + 4 * j];

	encrypt_block(aes, state);
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			aes->cipher_text[i + 4 * j] = state[4 * i + j];
}
