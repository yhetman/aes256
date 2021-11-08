/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/09/24 15:35:50 by yhetman                                  */
/*   Updated: 2021/11/07 21:34:15 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

static uint8_t*
allocate_w(t_aes *aes)
{
	uint8_t *w;

	switch (sizeof(aes->key))
	{
		default :
		case 16 :
			aes->N_k = 4;
			aes->N_r = 10;
			break;
		case 24 :
			aes->N_k = 6;
			aes->N_r = 12;
			break;
		case 32 :
			aes->N_k = 8;
			aes->N_r = 14;
			break;
	}

	w = (uint8_t *)malloc(sizeof(uint8_t) * (aes->N_r + 1) * 16);
	return (w);
}

void
init_t_aes(t_aes *aes, uint8_t *key, uint8_t *input)
{
	aes->key = key;
	aes->input = input;
	aes->w = allocate_w(aes);

	key_expansion(aes);
}


static int
get_flags(int argc, char ** argv, FILE ** input, FILE ** output,
	FILE **key, size_t *keysize, t_options *options)
{
    int 	flag,
    		check_flags;

    check_flags = 0;
    
    while ((flag = getopt(argc, argv, "i:o:s:k:m:deh")) != -1)
    {
        switch (flag)
        {
            case 'i':
                *input = fopen(optarg, "rb");
                check_flags++;
                break;
            case 'o':
                *output = fopen(optarg, "wb");
                check_flags++;
                break;
            case 's':
            	*keysize = atoi(optarg);
            	check_flags++;
            	break;
            case 'k':
                *key = fopen(optarg, "rb");
                check_flags++;
                break;
            case 'd':
                options->mode = false;
                break;
            case 'e':
                options->mode = true;
                break;
            case 'm':
                options->stream_mode = atoi(optarg);
                break;
            case 'h':
                printf("Usage:  ./aes -i ./input_file -o ./output_file -s {16 | 24 | 32} -k ./key_file\n");
                printf("Flags:\n");
                printf("\t-s\t-- specify the key length of AES.\n");
                printf("\t-e\t-- specify the encrypting process.\n");
                printf("\t-d\t-- specify the decrypting process.\n");
                printf("\t-m\t-- specify stream mode of AES.\n");
                printf("Available modes:\n\t\t1 -- ECB;\n");
                printf("\t\t2 -- CBC;\n");
                printf("\t\t3 -- CFB;\n");
                printf("\t\t4 -- OFB;\n");
                printf("\t\t5 -- CTR.\n");                
                return 1;
            case '?':
                fprintf(stderr, "%s unsuported flag.", optarg);
                return 1;
        }
    }
    if (check_flags < 4)
    {
        fprintf(stderr, "Needs to satisfy all parameters, use -h for help.\n");
        return 1;
    }

    return 0;
}


int
main(int argc, char **argv)
{
    FILE    	*input,
            	*outputfile,
            	*keyfile;
    t_options	options;
    size_t		keysize,
    			blocks;
    			// input_size;
    function    mode_;
    t_aes 		aes;
	char		byte[16];
	uint8_t 	*output,
				*initial_key;

	options.mode = true;
	options.stream_mode = 0;
	
    if (get_flags(argc, argv, &input, &outputfile, &keyfile, \
        &keysize, &options) != 0)
       return 1;

    mode_ = (options.mode == true) ? &cipher : &decipher;

	initial_key = (uint8_t*) malloc (sizeof(uint8_t) * keysize);

	if ((blocks = fread(initial_key, 1, keysize, keyfile)) != keysize)
    {
        printf("Error! Invalid key length!\n");
        exit(1);
    }

    if (options.stream_mode > 0 && options.stream_mode < 6)
    	initializer_for_stream_modes(initial_key, input, outputfile, &options);
    else
    {
    	while ((blocks = fread(byte, 1, 17, input)))
		{
			aes.input = NULL;
			aes.key = NULL;
			output = (uint8_t *)(byte);
			init_t_aes(&aes, initial_key, output);
			mode_(&aes);
			if (options.mode == false)
				fwrite(aes.decipher_text, 1, blocks, outputfile);
			else
				fwrite(aes.cipher_text, 1, blocks, outputfile);
			free(aes.w);
		}
	}
	free(initial_key);
    fclose(input);
    fclose(outputfile);
    fclose(keyfile);
    return 0;
}