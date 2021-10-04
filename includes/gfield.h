/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   gfield.h                                                                 */
/*                                                                            */
/*   By: yhetman <yhetman@student.unit.ua>                                    */
/*                                                                            */
/*   Created: 2021/10/02 13:19:36 by yhetman                                  */
/*   Updated: 2021/10/03 00:51:23 by yhetman                                  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFIELD_H
# define GFIELD_H

# include <stdint.h>

# define 		multiplication(x, y) multiplication_table[256 * x + y]	;
# define		xor(x, y) (x ^ y);

extern int8_t 	s_box[];
extern uint8_t 	inverse_s_box[];
extern uint8_t 	multiplication_table[];

#endif
