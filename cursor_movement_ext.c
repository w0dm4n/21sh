/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_ext.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 01:31:17 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 01:31:18 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	move_cursor_right(void)
{
	char	*res;

	if (((g_cursor_pos) / g_size.ws_col) < ((g_cursor_pos + 1) / g_size.ws_col))
		move_cursor_one_line_down();
	else
	{
		res = tgetstr("nd", NULL);
		tputs(res, 0, move_cursor);
	}
	g_cursor_pos++;
}

void	delete_x_characters(int to_del)
{
	char *res;

	res = tgetstr("DC", NULL);
	tputs(tgoto(res, 0, to_del), 1, move_cursor);
}

void	save_cursor_pos(void)
{
	char *res;

	res = tgetstr("sc", NULL);
	tputs(res, 0, move_cursor);
}

void	set_saved_cursor(void)
{
	char *res;

	res = tgetstr("rc", NULL);
	tputs(res, 0, move_cursor);
}

void	move_cursor_to(int pos)
{
	char *res;

	res = tgetstr("cm", NULL);
	tputs(tgoto(res, 0, pos), 1, move_cursor);
}
