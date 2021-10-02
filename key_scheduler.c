/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   key_scheduler.c                                                          */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 14:12:29 by yhetman                                  */
/*   Updated: 2021/10/02 14:12:30 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"


void		sub_word(uint8_t *w)
{

	uint8_t	i;

	for (i = 0; i < 4; i++)
		w[i] = s_box[w[i]];
}


void		rot_word(uint8_t *w)
{
	uint8_t	temp,
			i;

	temp = w[0];
	for (i = 0; i < 3; i++)
		w[i] = w[i + 1];
	w[3] = temp;
}


uint8_t		*Rcon(uint8_t i)
{
	uint8_t R[4] = {
					0x02, 0x00, 0x00, 0x00
				};

	if (i == 1)
		R[0] = 0x01;
	else if (i--; > 1)
	{
		R[0] = 0x02;
		//i--;
		while (i-- > 1)
		//{
			R[0] = multiplication(R[0], 0x02);
		//	i--;
		//}
	}
	
	return (R);
}


void		add_round_coeff(uint8_t *x, uint8_t	*r, uint8_t *y)
{
	uint8_t	i;

	for (i = 0; i < 4; i++)
		y[i] = xor(x[i], r[i]);
}


void		init_key_scheduler(t_aes *aes)
{
	uint8_t	temp[4],
			i,
			length;

	length = aes->N_b * (aes->N_r + 1);

	for (i = 0; i < aes->N_k; i++) {
		aes->w[4 * i + 0] = aes->key[4 * i + 0];
		aes->w[4 * i + 1] = aes->key[4 * i + 1];
		aes->w[4 * i + 2] = aes->key[4 * i + 2];
		aes->w[4 * i + 3] = aes->key[4 * i + 3];
	}

	for (i = aes->N_k; i < length; i++)
	{
		temp[0] = aes->w[4 * (i - 1) + 0];
		temp[1] = aes->w[4 * (i - 1) + 1];
		temp[2] = aes->w[4 * (i - 1) + 2];
		temp[3] = aes->w[4 * (i - 1) + 3];

		if (i % aes->N_k == 0)
		{
			rot_word(temp);
			sub_word(temp);
			add_round_coeff(temp, Rcon(i / aes->N_k), temp);
		}
		else if (aes->N_k > 6 && i % aes->N_k == 4)
			sub_word(temp);
		aes->w[4 * i + 0] = aes->w[4 * (i - aes->N_k) + 0] ^ temp[0];
		aes->w[4 * i + 1] = aes->w[4 * (i - aes->N_k) + 1] ^ temp[1];
		aes->w[4 * i + 2] = aes->w[4 * (i - aes->N_k) + 2] ^ temp[2];
		aes->w[4 * i + 3] = aes->w[4 * (i - aes->N_k) + 3] ^ temp[3];
	}
}