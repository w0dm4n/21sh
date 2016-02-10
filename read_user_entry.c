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

void	delete_current_character(void)
{
	char *res;

	res = tgetstr("dc", NULL);
	tputs(res, 0, move_cursor);
	g_cursor_pos--;
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

void	delete_x_characters(int to_del)
{
	char *res;

	res = tgetstr("DC", NULL);
	tputs(tgoto(res, 0, to_del), 1, move_cursor);
}

void	save_cursor_pos(void)
{
	char *res;

	res = tgetstr("sc", NULL);
	tputs(res, 0, move_cursor);
}

void	set_saved_cursor(void)
{
	char *res;

	res = tgetstr("rc", NULL);
	tputs(res, 0, move_cursor);
}
void	move_cursor_to(int pos)
{
	char *res;

	res = tgetstr("cm", NULL);
	tputs(tgoto(res, 0, pos), 1, move_cursor);
}

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
	write(1, g_cmd, ft_strlen(g_cmd));
	g_cursor_pos = old_pos;
	set_saved_cursor();
	move_cursor_left();
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

char	*add_in(char *g_cmd, int pos, char *toadd)
{
	char	*new_cmd;
	int		i;
	int		i_2;

	i = 0;
	i_2 = 0;
	if (!(new_cmd = malloc(sizeof(char) * READ_BUFFER)))
		return (NULL);
	while (g_cmd[i] && i != pos)
	{
		new_cmd[i] = g_cmd[i];
		i++;
	}
	i--;
	new_cmd[i] = toadd[0];
	i_2 = i;
	i++;
	while (g_cmd[i_2])
	{
		new_cmd[i] = g_cmd[i_2];
		i++;
		i_2++;
	}
	free(g_cmd);
	new_cmd[i] = '\0';
	return (new_cmd);
}

char	*del_in(char *g_cmd, int pos)
{
	char	*new_cmd;
	int		i;
	int		i_2;

	i = 0;
	i_2 = 0;
	if (!(new_cmd = malloc(sizeof(char) * READ_BUFFER)))
		return (NULL);
	while (g_cmd[i] && i != (pos - 1))
	{
		new_cmd[i] = g_cmd[i];
		i++;
	}
	i_2 = i;
	i++;
	while (g_cmd[i])
	{
		new_cmd[i_2] = g_cmd[i];
		i++;
		i_2++;
	}
	free(g_cmd);
	new_cmd[i_2] = '\0';
	return (new_cmd);
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
	else if (ascii_value == BACKSPACE && g_cursor_pos >= 1
		&& g_cmd[g_cursor_pos - 1])
	{
		g_cmd = del_in(g_cmd, g_cursor_pos);
		refresh_stdout_del(g_cmd);
	}
	else
	{
		if (ft_isprint(ascii_value))
		{
			g_cursor_pos++;
			if (g_cmd[g_cursor_pos + 1])
			{
				g_cmd = add_in(g_cmd, g_cursor_pos, buff);
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
		free(g_cmd);
		if (!(g_cmd = (char*)malloc(sizeof(char) * READ_BUFFER)))
			return ;
		ft_bzero(g_cmd, READ_BUFFER);
		g_cursor_pos = 0;
	}
	ft_bzero(buffer, READ_CHAR);
	read_user_entry(TRUE);
}
