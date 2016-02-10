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

int		move_cursor(int to_print)
{
	ft_putchar(to_print);
	return (to_print);
}

void	move_cursor_left(void)
{
	char *res;

	res = tgetstr("le", NULL);
	tputs(res, 0, move_cursor);
	g_cursor_pos--;
}

void	move_cursor_right(void)
{
	char *res;

	res = tgetstr("nd", NULL);
	tputs(res, 0, move_cursor);
	g_cursor_pos++;
}

char	*read_entry(char *buff)
{
	struct termios *term;
	int 			ascii_value;
	int				i;

	ascii_value = 0;
	i = 0;
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
		g_new_cmd = TRUE;
		write(1, "\n", 1);
		return (buff);
	}
	if (ascii_value == ARROW_LEFT)
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
	else
	{
		if (ft_isprint(ascii_value))
		{
			write(1, &ascii_value, 1);
			g_cursor_pos++;
			g_cmd = ft_strcat(g_cmd, buff);
		}
	}
	return (buff);
}

void		print_color_n_prompt(void)
{
	ft_putstr(COLOR_WHITE);
	ft_putstr("$> ");
}

void		read_user_entry(int read)
{
	char	*buffer;

	if (!(buffer = (char*)malloc(sizeof(char) * READ_CHAR)))
		return ;
	if (read)
		buffer = read_entry(buffer);
	if (g_new_cmd)
	{
		ft_putstr(g_cmd);
		ft_putstr("\n");
		//handle_cmd(g_cmd);
		print_color_n_prompt();
		g_new_cmd = FALSE;
		ft_bzero(g_cmd, READ_BUFFER);
		g_cursor_pos = 0;
	}
	ft_bzero(buffer, READ_CHAR);
	read_user_entry(TRUE);
}
