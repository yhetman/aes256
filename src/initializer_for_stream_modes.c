/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   initializer_for_stream_modes.c                                           */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/08 02:16:29 by yhetman                                  */
/*   Updated: 2021/11/08 02:16:31 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"



stream_modes	encrypting_functions[1] =
{
	&ecb_encrypting
	// &cbc_encrypting,
	// &cfb_encrypting,
	// &ofb_encrypting,
	// &ctr_encrypting
};

stream_modes	derypting_functions[1] =
{
	&ecb_decrypting,
// 	&cbc_decrypting,
// 	&cfb_decrypting,
// 	&ofb_decrypting,
// 	&ctr_decrypting
};

static void
redirect_to_stream_mode(t_options *options, uint8_t *buffer, uint8_t *key,
	uint8_t filesize)
{
	if (options->mode == true)
		encrypting_functions[options->stream_mode - 1](buffer, key, filesize);
	// else
	// 	decrypting_functions[options->stream_mode - 1](buffer, key, filesize);
}

void
initializer_for_stream_modes(uint8_t *initial_key,
	FILE *input, FILE *output, t_options *options)
{	
	uint8_t 	*buffer,
				padding = 0;
	uint8_t		blocks;

	fseek(input, 0, SEEK_END);
    blocks = ftell(input);
    fseek(input, 0, SEEK_SET);
    if (options->stream_mode == 2 || (options->stream_mode == 4 && options->mode == true))
    	blocks += 16;
    buffer = (uint8_t *)malloc(sizeof(uint8_t) *(blocks + padding));
	if(blocks % 16 != 0)
	{
		padding = (blocks / 16 + 1) * 16 - blocks;
		for(long i = blocks; i < blocks + padding; i++)
			buffer[i] = 32;
	}
	fread(buffer, 1, blocks, input);
	redirect_to_stream_mode(options, buffer, initial_key, blocks + padding);
	fwrite(buffer, 1, blocks + padding, output);
	free(buffer);
}