/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_ext_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 01:37:46 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 01:37:47 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	delete_current_line(void)
{
	char	*res;

	res = tgetstr("dl", NULL);
	tputs(res, 0, move_cursor);
	g_cursor_pos = 0;
}

void	reset_cursor(void)
{
	char	*res;

	res = tgetstr("cm", NULL);
	tputs(tgoto(res, 0, 0), 1, move_cursor);
}

void	move_cursor_on_the_last_word(char *g_cmd)
{
	while (g_cmd[g_cursor_pos] && g_cmd[g_cursor_pos] == ' ')
		move_cursor_left();
}

void	move_cursor_on_the_next_word(char *g_cmd)
{
	while (g_cmd[g_cursor_pos] && g_cmd[g_cursor_pos] == ' ')
		move_cursor_right();
}

void	go_home(char *g_cmd)
{
	if (g_cmd)
	{
		while (g_cursor_pos >= 1 && (g_cmd[g_cursor_pos]
		|| g_cmd[g_cursor_pos - 1]))
			move_cursor_left();
	}
}
