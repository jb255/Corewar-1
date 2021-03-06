NAME 						= unpack

CC							= gcc

C_DIR 						= srcs/

O_DIR 						= o/
LIBFT 						= ../libft/

H_DIR 						= -I ./includes/
LIBS_H_DIR					= -I ./libft/includes/

FLAGS =  -Wall -Werror -Wextra
INCURSES = -lncurses
LINKS = $(H_DIR) $(LIBS_H_DIR)
# C_FILES = $(shell ls -1 $(C_DIR) | grep "\.c")
C_FILES = hextodec.c main.c op.c read.c size_op.c op_get_size.c
O_FILES = $(addprefix $(O_DIR),$(C_FILES:.c=.o))

all:
	@make -C $(LIBFT)
	@make -j4 $(NAME)

$(NAME): $(O_FILES)
	@$(CC) $(CFLAGS) $(LIBS) $(H_DIR) $(O_FILES) $(FT_O) $(INCURSES) -L../libft -lft -o $(NAME) && printf "\033[0;32m" || printf "\033[0;31m"
	@echo -e "\033[1;32m"
	@echo ""
	@echo "_____"
	@echo "/ ____|"
	@echo "| |     ___  _ __ _____      ____ _ _ __ "
	@echo "| |    / _ \| '__/ _ \ \ /\ / / _\` | '__|"
	@echo "| |___| (_) | | |  __/\ V  V / (_| | |"
	@echo "\_____\___/|_|  \___| \_/\_/ \__,_|_|"
	@printf "%-24s\033[1;30m<<--\033[0;0m\n" "$@"

$(O_DIR)%.o: $(C_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(FLAGS) $(LINKS) -o $@ -c $< \
	&& printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" \
		&& exit 1)
clean:
	@rm $(O_FILES) $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@rmdir -p $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@mkdir $(O_DIR)
	@make -C $(LIBFT) clean

fclean: clean
	@rm $(NAME) 2> /dev/null || echo "" > /dev/null
	@make -C $(LIBFT) fclean

re: fclean all

print-%  : ; @echo $* = $($*)
.PHONY: all clean fclean re
