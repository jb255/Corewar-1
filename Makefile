# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaustry <jaustry@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 05:15:37 by jaustry           #+#    #+#              #
#    Updated: 2016/12/18 22:43:53 by vlancien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

all:
	make -C ./libft/
	make -C ./machine_virtuel/
	make -C ./assembleur/

clean:
	make -C ./libft/ clean
	make -C ./machine_virtuel/ clean
	make -C ./assembleur/ clean


fclean: clean
	make -C ./libft/ fclean
	make -C ./machine_virtuel/ fclean
	make -C ./assembleur/ fclean

re: fclean all
