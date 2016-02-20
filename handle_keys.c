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
	g_current_cmd++;
	g_logs_to_print = 0;
	reset_cursor();
	ft_putstr("$> ");
	g_selected_position = set_arr_zero(g_selected_position, READ_BUFFER);
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
			do_ls_f();
		else if (g_cursor_pos >= (int)ft_strlen(g_cmd))
			prompt_again_with_cmd();
		else
		{
			if (ft_strlen(g_cmd) != 1)
				backspace();
			else
			{
				g_cmd = meurs_en_enfer(g_cmd);
				refresh_stdout_del(g_cmd);
				ft_putstr_fd(" ", 1);
			}
		}
	}
}

void		print_or_add_in_stdout(int ascii_value, char *buff)
{
	if (ft_isprint(ascii_value))
	{
		if (g_cmd[g_cursor_pos + 1])
		{
			if ((ft_strlen(g_cmd) / (g_size.ws_col - 2)) <
				((ft_strlen(g_cmd) + 1) / (g_size.ws_col - 2)))
				return ;
			g_cursor_pos++;
			g_cmd = add_in(g_cmd, g_cursor_pos, buff, 0);
			refresh_stdout(g_cmd);
		}
		else
		{
			g_cursor_pos++;
			ft_putchar((char)ascii_value);
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
		if (g_cmd[(ft_strlen(g_cmd) - 1)] == '\\')
		{
			g_new_cmd = FALSE;
			g_multi_line = true;
			g_cursor_pos = 0;
			ft_putstr_fd("\n", 1);
		}
		else
		{
			g_new_cmd = TRUE;
			ft_putstr_fd("\n", 1);
			g_current_cmd++;
			g_logs_to_print = 0;
			g_multi_line = false;
		}
	}
}
