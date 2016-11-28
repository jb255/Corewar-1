/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 21:04:06 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/28 09:23:45 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "color.h"

int							ft_printf(char const *format, ...);
char						*ft_sprintf(char const *format, ...);
int							ft_printf_fd(int fd, char const *fmt, ...);
#endif
