/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   aes.h                                                                    */
/*                       													  */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/09/24 15:36:08 by yhetman                                  */
/*   Updated: 2021/10/03 00:21:06 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#ifndef AES_H
# define AES_H

# include "gfield.h"
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

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
	uint8_t		decipher_text[16];
}				t_aes;


/***			multiply.c 				***/
void			multiply_c(uint8_t *c, uint8_t *bytes, uint8_t * result);



/***			common_functions.c		***/
void			mix_columns(uint8_t *state, int N_b, uint8_t *c);
void 			add_round_key(uint8_t *state, uint8_t *w, uint8_t r, int N_b);


/***			key_scheduler.c 		***/
void			init_key_scheduler(t_aes *aes);


/***			aes_cipher.c 			***/
void 			cipher(t_aes *aes);


/***			aes_decipher.c 	 		***/
void 			decipher(t_aes *aes);


#endif
