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



stream_modes	encrypting_functions[4] =
{
	&ecb_encrypting,
	&cbc_encrypting,
	// &cfb_encrypting,
	&ofb_encrypting,
	&ctr
};

stream_modes	decrypting_functions[4] =
{
	&ecb_decrypting,
 	&cbc_decrypting,
// 	&cfb_decrypting,
	&ofb_decrypting,
	&ctr
};

static void
redirect_to_stream_mode(t_options *options, uint8_t *buffer, uint8_t *key, \
	size_t filesize)
{
	if (options->mode == true)
		encrypting_functions[options->stream_mode - 1](buffer, key, filesize);
	else
		decrypting_functions[options->stream_mode - 1](buffer, key, filesize);
}

void
initializer_for_stream_modes(uint8_t *initial_key,
	FILE *input, FILE *output, t_options *options)
{	
	uint8_t 	*buffer,
				padding = 0;


    if (options->stream_mode == 2 || (options->stream_mode == 4 && options->mode == true))
    	options->input_bytes += 16;
    buffer = (uint8_t *)malloc(sizeof(uint8_t) *(options->input_bytes + padding));
	if(options->input_bytes % 16 != 0)
	{
		padding = (options->input_bytes / 16 + 1) * 16 - options->input_bytes;
		for(size_t i = options->input_bytes; i < options->input_bytes + padding; i++)
			buffer[i] = 32;
	}
	
	fread(buffer, 1, options->input_bytes, input);
	
	redirect_to_stream_mode(options, buffer, initial_key, options->input_bytes + padding);
	
	fwrite(buffer, 1, options->input_bytes + padding, output);
	free(buffer);
}
