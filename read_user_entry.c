/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 03:15:16 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/09 03:15:27 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		go_end(char *g_cmd)
{
	if (g_cmd)
	{
		if (ft_strlen(g_cmd))
		{
			while (g_cmd[g_cursor_pos]
			|| g_cmd[g_cursor_pos - 1])
				move_cursor_right();
			move_cursor_left();
		}
	}
}

char		*read_entry(char *buff)
{
	struct termios	*term;
	int				ascii_value;
	int				i;
	int				cmd_size;

	ascii_value = 0;
	i = 0;
	cmd_size = 0;
	if (!(term = malloc(sizeof(struct termios))))
		return (NULL);
	if (!(tgetent(NULL, getenv("TERM"))))
		return (NULL);
	tcgetattr(0, term);
	term->c_lflag &= ~ICANON;
	term->c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, term);
	read(0, buff, READ_BUFFER);
	while (buff[i])
	{
		ascii_value += buff[i];
		i++;
	}
	if (ascii_value == NEW_CMD)
	{
		if (!check_special_chars(g_cmd))
		{
			g_new_cmd = FALSE;
			g_current_cmd++;
			g_cursor_pos = 0;
			return (buff);
		}
		else
		{
			g_new_cmd = TRUE;
			write(1, "\n", 1);
			g_current_cmd++;
			g_logs_to_print = 0;
			return (buff);
		}
	}
	else if (ascii_value == CTRL_U)
	{
		if (g_cursor_pos <= (g_size.ws_col - 3))
			return (buff);
		else if (g_cmd[g_cursor_pos - (g_size.ws_col - 3)])
			move_cursor_one_line_up();
	}
	else if (ascii_value == CTRL_B)
	{
		if (g_cmd[g_cursor_pos + (g_size.ws_col - 3)])
			move_cursor_one_line_down();
	}
	else if (ascii_value == CTRL_L)
	{
		ft_putstr(CLEAR_SCREEN);
		g_new_cmd = 1;
		g_current_cmd++;
		g_logs_to_print = 0;
		reset_cursor();
	}
	else if (ascii_value == CTRL_D)
	{
		cmd_size = ft_strlen(g_cmd);
		if (!g_cmd || !cmd_size)
		{
			ft_putstr("exit\n");
			exit(0);
		}
		else
		{
			if (g_cmd[cmd_size - 1] == ' ')
				ft_putstr("LS -F");
		}
	}
	else if (ascii_value == CTRL_G)
	{
		if (g_cmd)
			move_cursor_on_the_last_word(g_cmd);
	}
	else if (ascii_value == CTRL_R)
	{
		if (g_cmd)
			move_cursor_on_the_next_word(g_cmd);
	}
	else if (ascii_value == ARROW_LEFT)
	{
		if (g_cursor_pos >= 1)
		{
			move_cursor_left();
			return (buff);
		}
	}
	else if (ascii_value == ARROW_RIGHT)
	{
		if (ft_isprint(g_cmd[g_cursor_pos + 1]))
			move_cursor_right();
		else if (!ft_isprint(g_cmd[g_cursor_pos + 1])
			&& ft_isprint(g_cmd[g_cursor_pos]))
			move_cursor_right();
		return (buff);
	}
	else if (ascii_value == BACKSPACE && g_cursor_pos >= 1
		&& g_cmd[g_cursor_pos - 1])
	{
		g_cmd = del_in(g_cmd, g_cursor_pos);
		refresh_stdout_del(g_cmd);
	}
	else if (ascii_value == ARROW_UP)
	{
		print_logs(g_logs[g_logs_to_print]);
		if (g_logs[g_logs_to_print])
		{
			if (ft_strlen(g_logs[g_logs_to_print]))
				g_logs_to_print++;
		}
		return (buff);
	}
	else if (ascii_value == ARROW_DOWN)
	{
		if (g_logs_to_print)
		{
			g_logs_to_print--;
			print_logs(g_logs[g_logs_to_print]);
		}
	}
	else if (ascii_value == CTRL_S)
	{
		g_selected_position[g_cursor_pos] = 1;
		refresh_stdout_selected(g_cmd);
	}
	else if (ascii_value == CTRL_E)
	{
		g_cmd = get_new_cmdncopy(g_cmd, g_selected_position);
		g_selected_position = set_arr_zero(g_selected_position, READ_BUFFER);
	}
	else if (ascii_value == HOME)
		go_home(g_cmd);
	else if (ascii_value == END)
		go_end(g_cmd);
	else
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
	return (buff);
}

void		read_user_entry(int read)
{
	char	*buffer;

	ioctl(0, TIOCGWINSZ, &g_size);
	if (!(buffer = (char*)malloc(sizeof(char) * READ_CHAR)))
		return ;
	(read) ? (buffer = read_entry(buffer)) : print_color_n_prompt();
	if (g_new_cmd)
	{
		ft_putstr(g_cmd);
		ft_putstr("\n");
		//handle_cmd(g_cmd);
		if (g_cmd[0])
			g_logs = add_in_front(g_logs, g_cmd);
		print_color_n_prompt();
		g_new_cmd = FALSE;
		free(g_cmd);
		if (!(g_cmd = (char*)malloc(sizeof(char) * READ_BUFFER)))
			return ;
		ft_bzero(g_cmd, READ_BUFFER);
		g_cursor_pos = 0;
		g_selected_position = set_arr_zero(g_selected_position, READ_BUFFER);
	}
	ft_bzero(buffer, READ_CHAR);
	read_user_entry(TRUE);
}
