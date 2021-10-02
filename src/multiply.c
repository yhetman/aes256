/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   multiply.c                                                               */
/*                                                                            */
/*   By: blukasho <blukasho@ustork.com.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 22:16:50 by blukasho                                 */
/*   Updated: 2021/10/03 00:12:14 by blukasho                                 */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

void	multiply_c(uint8_t *c, uint8_t *bytes, uint8_t *result)
{
	result[0] = multiplication_table[256 * c[0] + bytes[0]]^multiplication_table[256 * c[3] + bytes[1]]^multiplication_table[256 * c[2] + bytes[2]]^multiplication_table[256 * c[1] + bytes[3]]; 
	result[1] = multiplication_table[256 * c[1] + bytes[0]]^multiplication_table[256 * c[0] + bytes[1]]^multiplication_table[256 * c[3] + bytes[2]]^multiplication_table[256 * c[2] + bytes[3]]; 
	result[2] = multiplication_table[256 * c[2] + bytes[0]]^multiplication_table[256 * c[1] + bytes[1]]^multiplication_table[256 * c[0] + bytes[2]]^multiplication_table[256 * c[3] + bytes[3]]; 
	result[3] = multiplication_table[256 * c[3] + bytes[0]]^multiplication_table[256 * c[2] + bytes[1]]^multiplication_table[256 * c[1] + bytes[2]]^multiplication_table[256 * c[0] + bytes[3]];
}


