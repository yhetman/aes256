/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   mix.c                                                                    */
/*                                                                            */
/*   By: blukasho <blukasho@ustork.com.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 22:21:06 by blukasho                                 */
/*   Updated: 2021/10/02 23:53:57 by blukasho                                 */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

void	mix_columns(uint8_t *state, int N_b)
{

//	uint8_t	c[4] =	{0x02, 0x01, 0x01, 0x03};

	uint8_t i,
			j,
//			column[4],
			result[4];

	for (j = 0; j < N_b; j++)
	{
		for (i = 0; i < 4; i++)
			;
//			column[i] = state[N_b * i + j];

		// multiply_c(c, column, result);

		for (i = 0; i < 4; i++)
			state[N_b * i + j] = result[i];
	}
}
