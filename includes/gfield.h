/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   gfield.h                                                                 */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 13:19:36 by yhetman                                  */
/*   Updated: 2021/10/03 00:51:23 by blukasho                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFIELD_H
# define GFIELD_H
# define multiplication(x, y) multiplication_table[256 * x + y]	;
# define xor(x, y) (x ^ y);

# include <stdint.h>

extern int8_t s_box[];
extern uint8_t inverse_s_box[];
extern uint8_t multiplication_table[];

#endif
