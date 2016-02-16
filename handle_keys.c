/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 03:24:21 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 03:24:38 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		control_e(void)
{
	g_cmd = get_new_cmdncopy(g_cmd, g_selected_position);
	g_selected_position = set_arr_zero(g_selected_position, READ_BUFFER);
}

void		clear_screen_term(void)
{
	ft_putstr(CLEAR_SCREEN);
	g_new_cmd = 1;
	g_current_cmd++;
	g_logs_to_print = 0;
	reset_cursor();
}

void		control_d(int size)
{
	if (!g_cmd || !size)
	{
		ft_putstr("exit\n");
		exit(0);
	}
	else
	{
		if (g_cmd[size - 1] == ' ')
			ft_putstr("LS -F");
	}
}

void		print_or_add_in_stdout(int ascii_value, char *buff)
{
	if (ft_isprint(ascii_value))
	{
		g_cursor_pos++;
		if (g_cmd[g_cursor_pos + 1])
		{
			g_cmd = add_in(g_cmd, g_cursor_pos, buff, 0);
			refresh_stdout(g_cmd);
		}
		else
		{
			write(1, &ascii_value, 1);
			g_cmd = ft_strcat(g_cmd, buff);
		}
	}
}

void		enter_key(void)
{
	if (!check_special_chars(g_cmd))
	{
		g_new_cmd = FALSE;
		g_current_cmd++;
		g_cursor_pos = 0;
	}
	else
	{
		g_new_cmd = TRUE;
		write(1, "\n", 1);
		g_current_cmd++;
		g_logs_to_print = 0;
	}
}
