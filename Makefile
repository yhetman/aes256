#* ************************************************************************** *#
#*                                                                            *#
#*                                                                            *#
#*   Makefile                                                                 *#
#*                                                                            *#
#*   By: yhetman <yhetman@student.unit.ua>                                    *#
#*                                                                            *#
#*   Created: 2021/10/02 20:08:48 by yhetman                                  *#
#*   Updated: 2021/10/03 00:37:12 by yhetman                                  *#
#*                                                                            *#
#* ************************************************************************** *#

SRCS = aes_cipher.c aes_decipher.c reading.c key_expansion.c \
	print_uint8_t.c multiply.c common_functions.c \
	initializer_for_stream_modes.c \
	ecb.c cbc.c ofb.c ctr.c

SRCS_DIR = src/

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

OBJ_DIR = obj/

LIB_NAME = libaes.a

AES = aes

FLAGS = -I includes -Wall -Wextra -Werror

DEBUG_FLAGS = -g3 -fsanitize=address

AES_MAIN = src/main.c

all: make_obj_dir $(AES)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	gcc $(FLAGS) -c $< -o $@

$(LIB_NAME): $(OBJ)
	ar -rv $(LIB_NAME) $^
	ranlib $(LIB_NAME)

$(AES): $(LIB_NAME) $(AES_MAIN)
	gcc $(FLAGS) $(AES_MAIN) $(LIB_NAME) -o $(AES)

make_obj_dir:
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(AES)
	rm -f $(LIB_NAME)

re: fclean all

.PHONY: all clean flcean re debug
