/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 01:29:13 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 01:29:14 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		move_cursor(int to_print)
{
	ft_putchar(to_print);
	return (to_print);
}

void	delete_current_character(void)
{
	char *res;

	res = tgetstr("dc", NULL);
	tputs(res, 0, move_cursor);
	g_cursor_pos--;
}

void	move_cursor_one_line_up(void)
{
	char	*res;

	res = tgetstr("up", NULL);
	tputs(res, 0, move_cursor);
	g_cursor_pos = (g_cursor_pos - (g_size.ws_col - 3));
}

void	move_cursor_left(void)
{
	char *res;

	res = tgetstr("le", NULL);
	tputs(res, 0, move_cursor);
	g_cursor_pos--;
}

void	move_cursor_one_line_down(void)
{
	char	*res;
	int		old_pos;

	old_pos = g_cursor_pos;
	res = tgetstr("do", NULL);
	tputs(res, 0, move_cursor);
	while (g_cursor_pos)
	{
		if (((old_pos) / g_size.ws_col) < ((g_cursor_pos) / g_size.ws_col))
			break ;
		g_cursor_pos++;
	}
}
