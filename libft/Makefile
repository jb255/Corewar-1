# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 20:28:54 by vlancien          #+#    #+#              #
#    Updated: 2016/12/20 04:48:03 by vlancien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 							= libft.a
CC								= gcc
H_DIR 							= -I ./includes/
SUB1_DIR 							= basic/
SUB2_DIR 							= gnl/
SUB3_DIR 							= list/
SUB4_DIR 							= ft_printf/

O_DIR 						= o/

FLAGS = -Wall -Werror -Wextra
LINKS =

C_FILES = cmp.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isegal.c ft_islower.c ft_isprint.c ft_isupper.c ft_itoa.c \
ft_itoa_base.c ft_len.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_power.c ft_putchar.c \
ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
ft_putstr.c ft_putstr_fd.c ft_str_ext_split.c ft_str_reg_chr.c ft_strcat.c \
ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c \
ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c \
ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
ft_strtrim.c ft_tolower.c ft_toupper.c to_lower.c ft_alternate.c \
ft_apply_flag.c ft_base.c ft_call_char.c ft_call_errno.c ft_call_float.c \
ft_call_int.c ft_call_percent.c ft_call_pointer.c ft_call_wildcard.c \
ft_call_wstring.c ft_char_type.c ft_check_fmt.c ft_conv_exp.c ft_conv_float.c \
ft_conv_wchar.c ft_double_type.c ft_free_list.c ft_get_accuracy.c ft_get_args.c \
ft_get_fmt.c ft_get_greatest_modifier.c ft_get_width.c ft_int_type.c \
ft_is_format.c ft_is_modifier.c ft_is_valid.c ft_make_node.c ft_move_index.c \
ft_printf.c ft_printf_fd.c ft_repstr.c ft_round.c ft_set_length.c \
ft_set_width.c ft_strset.c ft_transfer_wchar.c ft_transfer_wchars.c \
ft_type_crossroad.c get_next_line.c ft_create_elem.c ft_list_at.c \
ft_list_clear.c ft_list_find.c ft_list_foreach.c ft_list_foreach_if.c \
ft_list_last.c ft_list_merge.c ft_list_push_back.c ft_list_push_front.c \
ft_list_push_param.c ft_list_remove_if.c ft_list_reverse.c \
ft_list_reverse_fun.c ft_list_size.c ft_list_sort.c ft_listwrd.c \
ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c \
ft_lstnew.c ft_lstswap.c ft_sorted_list_insert.c ft_sorted_list_merge.c
O_FILES = $(addprefix $(O_DIR),$(C_FILES:.c=.o))

all:
	@make -j4 $(NAME);

$(NAME): $(O_DIR) $(O_FILES)
	@ar rcs $@ $(O_FILES) && printf "\033[0;32m" || printf "\033[0;31m"
	@echo " _       _   _____   _____   _____  "
	@echo "| |     | | |  _  \ |  ___| |_   _| "
	@echo "| |     | | | |_| | | |__     | |   "
	@echo "| |     | | |  _  { |  __|    | |   "
	@echo "| |___  | | | |_| | | |       | |   "
	@echo "|_____| |_| |_____/ |_|       |_|   "
	@printf "%-24s\033[1;30m<<--\033[0;0m\n" "$@"

$(O_DIR)%.o: $(SUB1_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(H_DIR) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
		&& exit 1)

$(O_DIR)%.o: $(SUB2_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(H_DIR) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
	&& exit 1)

$(O_DIR)%.o: $(SUB3_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(H_DIR) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
	&& exit 1)

$(O_DIR)%.o: $(SUB4_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(H_DIR) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
	&& exit 1)
clean:
	@rm $(O_FILES) $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@rmdir -p $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@mkdir $(O_DIR)

fclean: clean
	@rm $(NAME) 2> /dev/null || echo "" > /dev/null

re: fclean all

print-%  : ; @echo $* = $($*)

.PHONY: all clean fclean re
