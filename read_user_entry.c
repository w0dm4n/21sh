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

char		*read_entry_suite_ext(char *buff, int ascii_value)
{
	if (ascii_value == CTRL_E)
		control_e();
	else if (ascii_value == HOME)
		go_home(g_cmd);
	else if (ascii_value == END)
		go_end(g_cmd);
	else if (ascii_value == ARROW_DOWN)
		arrow_down();
	else if (ascii_value == CTRL_S)
		control_s();
	else if (ascii_value == TABULATION)
		seek_and_print(g_cmd);
	else
		print_or_add_in_stdout(ascii_value, buff);
	return (buff);
}

char		*read_entry_suite(char *buff, int ascii_value)
{
	if (ascii_value == CTRL_G && g_cmd)
		move_cursor_on_the_last_word(g_cmd);
	else if (ascii_value == CTRL_R && g_cmd)
		move_cursor_on_the_next_word(g_cmd);
	else if (ascii_value == ARROW_LEFT)
		arrow_left();
	else if (ascii_value == ARROW_RIGHT)
		arrow_right();
	else if (ascii_value == BACKSPACE && g_cursor_pos >= 1
		&& g_cmd[g_cursor_pos - 1])
		backspace();
	else if (ascii_value == ARROW_UP)
		arrow_up();
	else if (ascii_value == CTRL_L)
		clear_screen_term();
	else if (ascii_value == CTRL_D)
		control_d(ft_strlen(g_cmd));
	return (read_entry_suite_ext(buff, ascii_value));
}

char		*read_entry(char *buff)
{
	struct termios	*term;
	int				ascii_value;
	int				cmd_size;

	ascii_value = 0;
	cmd_size = 0;
	term = g_term;
	if (!(tgetent(NULL, getenv("TERM"))))
		return (NULL);
	tcgetattr(0, term);
	term->c_lflag &= ~ICANON;
	term->c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, term);
	read(0, buff, READ_BUFFER);
	ascii_value = get_ascii_value(buff);
	if (ascii_value == NEW_CMD)
		enter_key();
	else if (ascii_value == CTRL_U)
		move_up();
	else if (ascii_value == CTRL_B)
		move_down();
	return (read_entry_suite(buff, ascii_value));
}

void		read_user_entry(int read)
{
	char	*buffer;

	ioctl(0, TIOCGWINSZ, &g_size);
	if (!(buffer = (char*)malloc(sizeof(char) * READ_CHAR)))
		return ;
	(read) ? (buffer = read_entry(buffer)) : print_color_n_prompt();
	if (g_new_cmd && buffer)
	{
		dup_or_close_fd();
		handle_wildcards();
		if (g_multi_line)
			g_cmd = get_multi_line_cmd(g_cmd);
		handle_all_cmds(g_cmd);
		if (g_cmd[0] && ft_is_one_printable(g_cmd))
			g_logs = add_in_front(g_logs, g_cmd);
		print_color_n_prompt();
		clear_all_n_realloc();
	}
	ft_bzero(buffer, READ_CHAR);
	read_user_entry(TRUE);
}
