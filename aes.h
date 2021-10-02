/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   aes.h                                                                    */
/*                         
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/09/24 15:36:08 by yhetman                                  */
/*   Updated: 2021/09/24 15:36:11 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#ifndef AES_H
# define AES_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include "gfield.h"



// # define	multiplication(x, y) multiplication_table[256 * x + y];
# define	xor(x, y) (x ^ y);


typedef struct 	s_aes
{
	int 		N_k;
	int 		N_r;
	int 		N_b;
	int 		K;
	uint8_t		*key;
	uint8_t		*w;
	uint8_t		*input;
	uint8_t		cipher_text[16];
}				t_aes;

void		multiply_c(uint8_t *c, uint8_t *bytes, uint8_t * result);

void		init_key_scheduler(t_aes *aes);
uint8_t		*allocate_w(t_aes *aes);
void		init_t_aes(t_aes *aes, uint8_t *key, uint8_t *input);
//t_aes		init_t_aes(uint8_t *key, uint8_t *input);

void		init_t_aes(t_aes *aes, uint8_t *key, uint8_t *input);
void		mix_columns(uint8_t *state, int N_b);
void 		cipher(t_aes *aes);


#endif

