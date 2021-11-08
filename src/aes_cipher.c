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
sub_bytes(uint8_t *state, int N_b)
{

	uint8_t	i,
			j;
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < N_b; j++)
			state[N_b * i + j] = s_box[state[N_b * i + j]];
}


static void
shift_rows(uint8_t *state, int N_b)
{

	uint8_t	i,
			j,
			k,
			temp;

	for (i = 1; i < 4; i++)
	{
		for (k = 0; k < i; k++)
		{
			temp = state[N_b * i + 0];
			
			for (j = 1; j < N_b ;  j++)
				state[N_b * i + j - 1] = state[N_b * i + j];

			state[N_b * i + N_b - 1] = temp;
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
	

	add_round_key(state, aes->w, 0, aes->N_b);

	for (round = 1; round < aes->N_r; round++)
	{
		sub_bytes(state, aes->N_b);
		shift_rows(state, aes->N_b);
		mix_columns(state, aes->N_b, c);
		add_round_key(state, aes->w, round, aes->N_b);
	}

	sub_bytes(state, aes->N_b);
	shift_rows(state, aes->N_b);
	add_round_key(state, aes->w, aes->N_r, aes->N_b);
}

void
cipher(t_aes *aes)
{
	uint8_t	state[4 * aes->N_b],
			i,
			j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < aes->N_b; j++)
			state[aes->N_b * i + j] = aes->input[i + 4 * j];

	encrypt_block(aes, state);
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < aes->N_b; j++)
			aes->cipher_text[i + 4 * j] = state[aes->N_b * i + j];
}
