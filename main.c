/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/09/24 15:35:50 by yhetman                                  */
/*   Updated: 2021/09/24 15:35:54 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

int 	main()
{
	t_aes 	*aes;
	uint8_t	i;

	uint8_t initial_key[] = {
		0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b,
		0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13,
		0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b,
		0x1c, 0x1d, 0x1e, 0x1f};

	uint8_t input[] = {
		0x00, 0x11, 0x22, 0x33,
		0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xaa, 0xbb,
		0xcc, 0xdd, 0xee, 0xff};
	
	uint8_t cipher_text[16]; // 128

	uint8_t *key_schedule; // expanded key

	aes = init_t_aes(initial_key, input);

	aes_key_expansion(initial_key, key_schedule);


	free(key_schedule);

	return 0;
}