/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   aes.h                                                                    */
/*                       													  */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/09/24 15:36:08 by yhetman                                  */
/*   Updated: 2021/10/03 00:21:06 by blukasho                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef AES_H
# define AES_H

# include "gfield.h"
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

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
//void		init_t_aes(t_aes *aes, uint8_t *key, uint8_t *input);
void		inverse_mix_columns(uint8_t *state, int N_b);
void		inverse_sub_bytes(uint8_t *state, int N_b);
//t_aes		init_t_aes(uint8_t *key, uint8_t *input);
void		mix_columns(uint8_t *state, int N_b);
void		init_key_scheduler(t_aes *aes);
uint8_t		*allocate_w(t_aes *aes);
void 		cipher(t_aes *aes);


#endif
