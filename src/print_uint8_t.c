/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   print_uint8_t.c                                                          */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/11/08 01:04:22 by yhetman                                  */
/*   Updated: 2021/11/08 01:04:25 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

void 		print_uint8_t(uint8_t *str)
{
	uint8_t i;

	for (i = 0; i < 4; i++)
		printf("%02x %02x %02x %02x " , str[4 * i + 0], str[4 * i + 1], str[4 * i + 2], str[4 * i + 3]);
	printf("\n");
}
 
