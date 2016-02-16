/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_suite_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 03:57:46 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 03:57:47 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	backspace(void)
{
	g_cmd = del_in(g_cmd, g_cursor_pos);
	refresh_stdout_del(g_cmd);
}

void	move_up(void)
{
	if (g_cursor_pos <= (g_size.ws_col - 3))
		return ;
	else if (g_cmd[g_cursor_pos - (g_size.ws_col - 3)])
		move_cursor_one_line_up();
}

void	move_down(void)
{
	if (g_cmd[g_cursor_pos + (g_size.ws_col - 3)])
		move_cursor_one_line_down();
}
