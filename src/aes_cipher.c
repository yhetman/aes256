/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   aes_cipher.c                                                             */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 13:29:02 by yhetman                                  */
/*   Updated: 2021/10/02 23:53:57 by blukasho                                 */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

static void	sub_bytes(uint8_t *state, int N_b)
{

	uint8_t	i,
			j;
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < N_b; j++)
			state[N_b * i + j] = s_box[state[N_b * i + j]];
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
