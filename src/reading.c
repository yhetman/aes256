/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   reading.c                                                                */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/04 17:22:17 by yhetman                                  */
/*   Updated: 2021/10/04 22:13:31 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


static void	print_uint8_t(uint8_t *str)
{
	int		i;

	for (; *str; str++)
	{
		i = (int)*str;
		printf("%02x ", i);
	}
	printf("\n");
}

int			main() {
	FILE	*f_gets = fopen("hexNumbers.txt", "r");
	char	byte[16];
	uint8_t *output;

		if(f_gets == NULL)
			return (printf("Please point to a valid key file!\n"));

		while (fgets(byte, 17, f_gets))
		{
			output = (uint8_t *)(byte);
			print_uint8_t(output);
		}
	
		fclose(f_gets);
	return 0;
}
