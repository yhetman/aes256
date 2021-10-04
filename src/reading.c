/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   reading.c                                                                */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/04 17:22:17 by yhetman                                  */
/*   Updated: 2021/10/04 22:10:13 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


static void
print_uint8_t(uint8_t *str)
{
	uint8_t i;

	for (i = 0; i < 4; i++)
		printf("%02x %02x %02x %02x ", str[4 * i + 0], str[4 * i + 1], str[4 * i + 2], str[4 * i + 3]);
	printf("\n");
}

int main() {
	FILE *f_gets = fopen("hexNumbers.txt", "r");
	if(f_gets == NULL)
	{
		printf("Please point to a valid key file!\n");
		fclose(f_gets);
		
		return 0;
	}
	char byte[16];
	
	uint8_t *output;
	while ( fgets (byte, 16, f_gets)!= NULL )
	{
		output = (uint8_t *)(byte);
		print_uint8_t(output);
	
	}
	fclose(f_gets);
return 0;
}
