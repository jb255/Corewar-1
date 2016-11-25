/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 17:13:17 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/25 07:40:57 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYERS_H
# define PLAYERS_H

// # include "corewar.h"

typedef struct s_process	t_process;
struct						s_process
{
	int						start;
	int						carry;
	int						position;
	int						wait_time;
	int						jumptodo;
	int						addr_pc;
	int						reg[REG_NUMBER];
	int						id_player;
	int						char_player;
	int						live_status;
};

typedef struct s_player		t_player;
struct						s_player
{
	char					*name;
	char					*comment;
	char					*path;
	unsigned long			size;
	int						start;
	int						size_func;
	int						carry;
	char					*file;
	int						id_player;
	int						position;
	int						jumptodo;
};


#endif
