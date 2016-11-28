# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 20:28:54 by vlancien          #+#    #+#              #
#    Updated: 2016/11/20 04:40:40 by mlevieux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 							= libft.a
CC								= gcc
H_DIR 							= -I ./includes/
SUB1_DIR 							= basic/
SUB2_DIR 							= gnl/
SUB3_DIR 							= list/
SUB4_DIR 							= ft_printf/
# SUB5_DIR 							= ft_printf/srcs/apply/
# SUB6_DIR 							= ft_printf/srcs/get/
# SUB7_DIR 							= ft_printf/srcs/int_calc/
# SUB8_DIR 							= ft_printf/srcs/tools/

O_DIR 						= o/

FLAGS = -Wall -Werror -Wextra
LINKS =

C_FILES = $(shell ls -1 $(SUB1_DIR) $(SUB2_DIR) $(SUB3_DIR) $(SUB4_DIR) | grep "\.c")

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

fclean: clean
	@rm $(NAME) 2> /dev/null || echo "" > /dev/null

re: fclean all

.PHONY: all clean fclean re
