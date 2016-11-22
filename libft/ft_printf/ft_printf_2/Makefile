# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/25 16:57:31 by mlevieux          #+#    #+#              #
#    Updated: 2016/05/14 09:44:36 by mlevieux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a # Nom de l'exec lib creee
CC = gcc # Compilateur
CFLAGS = -Wall -Werror -Wextra # Flags de compil'

INCDIR = libft
HEADERDIR = includes/
SRC = ft_alternate.c ft_call_percent.c ft_conv_float.c \
ft_get_greatest_modifier.c ft_move_index.c ft_transfer_wchar.c \
ft_apply_flag.c ft_call_pointer.c ft_conv_wchar.c ft_get_width.c \
ft_printf.c ft_transfer_wchars.c ft_base.c ft_call_wildcard.c \
ft_double_type.c ft_int_type.c ft_repstr.c ft_type_crossroad.c \
ft_call_char.c ft_call_wstring.c ft_free_list.c ft_is_format.c \
ft_round.c ft_call_errno.c ft_char_type.c \
ft_get_accuracy.c ft_is_modifier.c ft_set_length.c ft_call_float.c \
ft_check_fmt.c ft_get_args.c ft_is_valid.c ft_set_width.c \
ft_call_int.c ft_conv_exp.c ft_get_fmt.c ft_make_node.c ft_strset.c

OBJ = $(patsubst %c, %o, $(SRC))

HEADERS = $(addprefix $(HEADERDIR), $(patsubst %a, %h, $(NAME)))

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ) :
	gcc -Wall -Werror -Wextra -c $(SRC) -I $(HEADERDIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norme :
	norminette $(SRC) $(HEADERS)
