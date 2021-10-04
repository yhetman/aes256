/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   common_functions.c                                                       */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 22:21:06 by yhetman                                  */
/*   Updated: 2021/10/02 23:53:57 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

void
add_round_key(uint8_t *state, uint8_t *w, uint8_t r, int N_b)
{
	uint8_t	i,
			j;
	
	for (i = 0; i < N_b; i++)
		for (j = 0; j < 4; j++)
			state[N_b * j + i] = state[N_b * j + i]^w[4 * N_b * r + 4 * i + j];	
}


void
mix_columns(uint8_t *state, int N_b, uint8_t *c)
{
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
