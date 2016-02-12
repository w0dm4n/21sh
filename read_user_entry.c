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

void	delete_current_line(void)
{
	char	*res;

	res = tgetstr("dl", NULL);
	tputs(res, 0, move_cursor);
	g_cursor_pos = 0;
}

void	reset_cursor(void)
{
	char	*res;

	res = tgetstr("cm", NULL);
	tputs(tgoto(res, 0, 0), 1, move_cursor);
}

char	*get_args(char *buffer, int i, int i_2)
{
	int		size;
	char	*get_args;

	size = (ft_strlen(buffer + 1) - i);
	if (size)
	{
		if (!(get_args = (char*)malloc(sizeof(char) * size)))
			return (NULL);
		ft_bzero(get_args, size);
		while (buffer[i] != '\0' && buffer[i] != '\n')
		{
			if (buffer[i] == ' ')
			{
				while (buffer[i] == ' ')
					i++;
				i--;
			}
			get_args[i_2] = buffer[i];
			i_2++;
			i++;
		}
		get_args[i_2] = '\0';
		return (get_args);
	}
	return (NULL);
}

char		*get_real_cmd(char *buffer)
{
	char	*get_cmd;
	char	*cmdnargs;
	int		pos;
	int		i;
	int		res;

	i = 0;
	res = 0;
	get_cmd = NULL;
	cmdnargs = NULL;
	buffer = ft_strtrim(buffer);
	pos = ft_strposition(buffer, " ");
	cmdnargs = ft_strnew(6000);
	if (pos)
	{
		if (!(get_cmd = (char*)malloc(sizeof(char) * pos)))
			return (NULL);
		ft_bzero(get_cmd, pos);
		while (i < pos)
		{
			if (buffer[i] != '\n')
				get_cmd[i] = *ft_strdup(&buffer[i]);
			i++;
		}
	}
	get_cmd[i] = '\0';
	cmdnargs = ft_strcat(cmdnargs, get_cmd);
	if (get_args(buffer, i, 0))
		cmdnargs = ft_strcat(cmdnargs, get_args(buffer, i, 0));
	return (cmdnargs);
}

void	print_logs(char *to_print)
{
	int		i;
	char	*cmd;

	if (!to_print)
		return ;
	cmd = get_real_cmd(to_print);
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
	{
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
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

char	**alloc_cmd(char **current_cmd)
{
	if (!(current_cmd = malloc(sizeof(char*) * LOGS_BUFFER)))
		return (NULL);
	current_cmd = ft_set_null(current_cmd);
	return (current_cmd);
}

char 	**add_in_front(char **logs, char *cmd)
{
	char	**new_logs;
	int		i;
	int		i_2;

	i = 0;
	i_2 = 1;
	if (!(new_logs = malloc(sizeof(char*) * LOGS_BUFFER)))
		return (NULL);
	new_logs[0] = ft_strdup(cmd);
	while (logs[i])
	{
		if (logs[i])
		{
			new_logs[i_2] = ft_strdup(logs[i]);
			i_2++;
		}
		i++;
	}
	return (new_logs);
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

void	go_home(char *g_cmd)
{
	if (g_cmd)
	{
		while (g_cursor_pos >= 1 && (g_cmd[g_cursor_pos]
		|| g_cmd[g_cursor_pos - 1]))
			move_cursor_left();
	}
}

void	go_end(char *g_cmd)
{
	if (g_cmd)
	{
		if (ft_strlen(g_cmd))
		{
			while (g_cmd[g_cursor_pos]
			|| g_cmd[g_cursor_pos - 1])
				move_cursor_right();
			move_cursor_left(); // cuz of one more
		}
	}
}

void	move_cursor_on_the_last_word(char *g_cmd)
{
	while (g_cmd[g_cursor_pos] && g_cmd[g_cursor_pos] == ' ')
		move_cursor_left();
}

void	move_cursor_on_the_next_word(char *g_cmd)
{
	while (g_cmd[g_cursor_pos] && g_cmd[g_cursor_pos] == ' ')
		move_cursor_right();
}

char	*read_entry(char *buff)
{
	struct termios *term;
	int 			ascii_value;
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
	// CTRL C CLOSE CHILD IF THERE IS ONE
	if (ascii_value == NEW_CMD)
	{
		if (!check_special_chars(g_cmd))
		{
			g_new_cmd = TRUE;
			write(1, "\n", 1);
			g_current_cmd++:
			g_logs_to_print = 0;
			return ("\0");
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
	else if (ascii_value == CTRL_L)
	{
		ft_putstr(CLEAR_SCREEN);
		g_new_cmd = 1;
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
			// + print new prompt + current cmd
			// else print cmd again
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
	}
	ft_bzero(buffer, READ_CHAR);
	read_user_entry(TRUE);
}
