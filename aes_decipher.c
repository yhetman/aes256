/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   aes_decipher.c                                                           */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 13:51:29 by yhetman                                  */
/*   Updated: 2021/10/02 13:51:31 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */


#include "aes.h"

void	inverse_sub_bytes(uint8_t *state, int N_b)
{
	uint8_t	i,
			j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < N_b; j++)
			state[N_b * i + j] = inverse_s_box[state[N_b * i + j]];
}

void	inverse_mix_columns(uint8_t *state, int N_b)
{
	uint8_t	c[4] =
					{
						0x0e, 0x09, 0x0d, 0x0b
					}; // {0e} + {09}x + {0d}x2 + {0b}x3
	uint8_t	i,
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
