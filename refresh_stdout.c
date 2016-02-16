/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_stdout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 01:41:04 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 01:41:05 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	refresh_stdout_del(char *g_cmd)
{
	int old_pos;

	old_pos = g_cursor_pos;
	save_cursor_pos();
	while (g_cursor_pos >= 1)
		move_cursor_left();
	if (!ft_strlen(g_cmd))
		delete_x_characters(1);
	else
		delete_x_characters(ft_strlen(g_cmd));
	ft_putstr_fd(g_cmd, 1);
	g_cursor_pos = old_pos;
	set_saved_cursor();
	move_cursor_left();
	if (!ft_strlen(g_cmd))
		g_cursor_pos = 0;
}

void	refresh_stdout(char *g_cmd)
{
	int old_pos;

	old_pos = g_cursor_pos;
	save_cursor_pos();
	while (g_cursor_pos >= 1 && (g_cmd[g_cursor_pos]
		|| g_cmd[g_cursor_pos - 1]))
		move_cursor_left();
	delete_x_characters(ft_strlen(g_cmd));
	write(1, " ", 1);
	write(1, g_cmd, ft_strlen(g_cmd));
	g_cursor_pos = old_pos - 1;
	set_saved_cursor();
	move_cursor_right();
}

void	refresh_stdout_selected(char *g_cmd)
{
	int old_pos;
	int	i;

	i = 0;
	old_pos = g_cursor_pos;
	save_cursor_pos();
	while (g_cursor_pos >= 1 && (g_cmd[g_cursor_pos]
		|| g_cmd[g_cursor_pos - 1]))
		move_cursor_left();
	delete_x_characters(ft_strlen(g_cmd));
	while (g_cmd[i])
	{
		if (g_selected_position[g_cursor_pos])
			ft_putstr(PRINT_SELECTED);
		ft_putchar(g_cmd[i]);
		ft_putstr(RESET);
		ft_putstr(DEFAULT_COLOR);
		g_cursor_pos++;
		i++;
	}
}
