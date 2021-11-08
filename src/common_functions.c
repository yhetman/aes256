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

char
*random_string(char *str, size_t size)
{
	char 	charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	size_t 	n;

	for (n = 0; n < size; n++)
	{
		int key = rand() % (int) (sizeof charset - 1);
		str[n] = charset[key];
	}
	
	str[size] = '\0';

  return str;
}

void
add_round_key(uint8_t *state, uint8_t *w, uint8_t r)
{
	uint8_t	i,
			j;
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			state[4 * j + i] ^= w[16 * r + 4 * i + j];	
}


void
mix_columns(uint8_t *state, uint8_t *c)
{
	uint8_t i,
			j,
			column[4],
			result[4];

	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 4; i++)
			column[i] = state[4 * i + j];

		multiply_c(c, column, result);

		for (i = 0; i < 4; i++)
			state[4 * i + j] = result[i];
	}
}
