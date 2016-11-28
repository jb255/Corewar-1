# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaustry <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 05:15:37 by jaustry           #+#    #+#              #
#    Updated: 2016/11/28 05:15:41 by jaustry          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm2
NAME2 = corewar
CC = gcc
CFLAGS = -Wall -Wextra -Werror
ASM = ./compilateur/srcs/main.c \
./compilateur/srcs/op.c \
./compilateur/srcs/tools.c \
./compilateur/srcs/tools2.c \
./compilateur/srcs/func_error/asm_error.c \
./compilateur/srcs/parsing/ft_parse_match.c \
./compilateur/srcs/parsing/label.c \
./compilateur/srcs/parsing/method.c \
./compilateur/srcs/parsing/method2.c \
./compilateur/srcs/parsing/parsing.c \
./compilateur/srcs/parsing/parsing2.c \
./compilateur/srcs/parsing/parsing3.c \
./compilateur/srcs/parsing/parsing4.c \
./compilateur/srcs/parsing/parsing5.c \

COREWAR = 
OBJS = $(ASM:.c=.o) $(COREWAR:.c=.o)
RM = rm -f

.PHONY: all clean fclean re

all: $(NAME) #$(NAME2)

$(NAME): $(OBJS)
	make -C ./libft/
	$(CC) -o $(NAME) $(ASM) ./libft/libft.a

$(NAME2): $(OBJS)
	$(CC) -o $(NAME2) $(COREWAR) ./libft/libft.a

$(OBJS) : $(ASM) $(COREWAR) ./Makefile
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	make -C ./libft/ clean
	$(RM) $(OBJS)

fclean: clean
	make -C ./libft/ fclean
	$(RM) $(NAME)
	$(RM) $(NAME2)

re: fclean all

