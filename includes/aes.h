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
# include <stdbool.h>
# include <stdlib.h>
# include <inttypes.h>
# include <string.h>
# include <unistd.h>

typedef struct 	s_aes
{
	size_t 		N_k;
	size_t 		N_r;
	size_t 		K;
	uint8_t		*key;
	uint8_t		*w;
	uint8_t		*input;
	uint8_t		cipher_text[16];
	uint8_t		decipher_text[16];
}				t_aes;

typedef struct 	s_options
{
	bool		mode;
	int 		stream_mode;
	size_t		input_bytes;
}				t_options;

typedef void	(*stream_modes)(uint8_t*, uint8_t*, size_t);
typedef void 	(*function)(t_aes *);

/***			multiply.c 				***/
void			multiply_c(uint8_t *c, uint8_t *bytes, uint8_t * result);



/***			common_functions.c		***/
void			mix_columns(uint8_t *state, uint8_t *c);
void 			add_round_key(uint8_t *state, uint8_t *w, uint8_t r);
char			*random_string(char *str, size_t size);

/***			key_expansion.c 		***/
void			key_expansion(t_aes *aes);


/***			aes_cipher.c 			***/
void 			cipher(t_aes *aes);
void			encrypt_block(t_aes *aes, uint8_t *state);

/***			aes_decipher.c 	 		***/
void 			decipher(t_aes *aes);
void			decrypt_block(t_aes *aes, uint8_t *state);


/***			print_uint8_t.c 		***/
void 			print_uint8_t(uint8_t *str);


/***			initializer_for_stream_modes  ***/

void			init_t_aes(t_aes *aes, uint8_t *key, uint8_t *input);

void			initializer_for_stream_modes(uint8_t *initial_key,
				FILE *input, FILE *output, t_options *options);


/***			ecb 		  ***/
void			ecb_encrypting(uint8_t *input, uint8_t*key, size_t input_legth);
void			ecb_decrypting(uint8_t *input, uint8_t*key, size_t input_legth);

/***			cbc 		  ***/
void			cbc_decrypting(uint8_t *input, uint8_t *key, size_t input_legth);
void			cbc_encrypting(uint8_t *input, uint8_t *key, size_t input_legth);


/***			cfb 		  ***/
void			cfb_encrypting(uint8_t *input, uint8_t *key, size_t input_legth);
void			cfb_decrypting(uint8_t *input, uint8_t *key, size_t input_legth);


/***			ofb 		  ***/
void			ofb_decrypting(uint8_t *input, uint8_t *key, size_t input_legth);
void			ofb_encrypting(uint8_t *input, uint8_t *key, size_t input_legth);

/***			ctr 		  ***/
void			ctr(uint8_t *input, uint8_t*key, size_t input_legth);

#endif
