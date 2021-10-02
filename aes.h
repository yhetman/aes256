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



# define	multiplication(x, y) multiplication_table[256 * x + y]	;
# define	xor(x, y) (x ^ y);


typedef struct 	s_aes
{
	int 		N_k;
	int 		N_r;
	int 		N_b;
	int 		key;
	uint8_t		*key;
	uint8_t		*w;
	uint8_t		*state;
}				t_aes;

void		multiply_c(uint8_t *c, uint8_t *bytes, uint8_t * result);

void		init_key_scheduler(t_aes *aes);
uint8_t		*allocate_w(t_aes *aes);
t_aes		init_t_aes(uint8_t *key, uint8_t *input);



#endif

