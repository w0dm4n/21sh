/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_suite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 03:51:42 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 03:51:48 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	control_s(void)
{
	g_selected_position[g_cursor_pos] = 1;
	refresh_stdout_selected(g_cmd);
}

void	arrow_down(void)
{
	if (g_logs_to_print)
	{
		g_logs_to_print--;
		print_logs(g_logs[g_logs_to_print]);
	}
}

void	arrow_up(void)
{
	print_logs(g_logs[g_logs_to_print]);
	if (g_logs[g_logs_to_print])
	{
		if (ft_strlen(g_logs[g_logs_to_print]))
			g_logs_to_print++;
	}
}

void	arrow_right(void)
{
	if (ft_isprint(g_cmd[g_cursor_pos + 1]))
		move_cursor_right();
	else if (!ft_isprint(g_cmd[g_cursor_pos + 1])
		&& ft_isprint(g_cmd[g_cursor_pos]))
		move_cursor_right();
}

void	arrow_left(void)
{
	if (g_cursor_pos >= 1)
	{
		move_cursor_left();
		return (buff);
	}
}