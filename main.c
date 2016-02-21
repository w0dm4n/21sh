/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 09:43:46 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/08 09:44:24 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	reset_all_value(void)
{
	g_selected_position = set_arr_zero(g_selected_position, READ_BUFFER);
	g_cursor_pos = 0;
	g_current_cmd = 0;
	g_logs_to_print = 0;
	g_multi_line = 0;
}

int		main(int argc, char **argv, char **env)
{
	g_env = env;
	if (!g_env || !g_env[0])
	{
		ft_putstr_fd("21sh can't work without environment !\n", 2);
		return (0);
	}
	if (argc != 1 || argv[1])
		ft_putstr_fd("21sh do not take any argument !\n", 2);
	else
	{
		grab_signal_n_alloc();
		reset_all_value();
		if (!(g_logs = alloc_cmd(g_logs)))
			return (-1);
		if (!(g_cmd = ft_strnew(READ_BUFFER)))
			return (-1);
		g_new_cmd = FALSE;
		read_user_entry(FALSE);
	}
	return (0);
}
