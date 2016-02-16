/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_logs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 01:43:13 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 01:43:14 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	print_logs_suite(char *cmd)
{
	int i;

	i = 0;
	while (g_cursor_pos >= 1 && (g_cmd[g_cursor_pos]
		|| g_cmd[g_cursor_pos - 1]))
		move_cursor_left();
	delete_x_characters(ft_strlen(g_cmd));
	g_cursor_pos = 0;
	if (g_cmd)
		free(g_cmd);
	g_cmd = ft_strdup(cmd);
	while (g_cmd[i])
	{
		ft_putchar(g_cmd[i]);
		g_cursor_pos++;
		i++;
	}
}

void	print_logs(char *to_print)
{
	int		i;
	char	*cmd;

	if (!to_print)
		return ;
	cmd = get_real_cmd(to_print, 0, 0, NULL);
	i = 0;
	if (!g_cursor_pos)
	{
		while (cmd[i])
		{
			ft_putchar(cmd[i]);
			g_cmd[i] = cmd[i];
			g_cursor_pos++;
			i++;
		}
	}
	else
		print_logs_suite(cmd);
}
