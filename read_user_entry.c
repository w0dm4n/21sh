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

int		my_outc(int to_print)
{
	ft_putchar(to_print);
	return (to_print);
}

void	move_cursor_left(int x, int y)
{
	char *res;

	x = 1;
	y = 1;
	res = tgetstr("le", NULL);
	tputs(res, 0, my_outc);
	//ft_putstr(res);
	//tputs(tgoto(res, 200, 25), 1, my_outc);
}

char		*read_entry(char *buff)
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
	if (ft_isprint(ascii_value))
		write(1, &ascii_value, 1);
	if (ascii_value == NEW_CMD)
	{
		g_new_cmd = TRUE;
		write(1, "\n", 1);
		return (buff);
	}
	if (ascii_value == BACKSPACE)
	{
		move_cursor_left(1, 1);
		//ft_putstr_fd(PRINT_CURSOR_POS, 2);
		//term->c_lflag &= ~ECHO;
		//tcsetattr(0, TCSANOW, term);
	/*	int fd = open("test", O_RDWR);
		char test[1024];
		write(fd, PRINT_CURSOR_POS, 10);
		read(fd, test, 1024);
		ft_putchar(test[0]);
		//write(3, PRINT_CURSOR_POS, 10);
		//move_cursor_left(1, 1);
		//tputs(res, 0,my_outc); */
	}
	g_cmd = ft_strcat(g_cmd, buff);
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
	}
	ft_bzero(buffer, READ_CHAR);
	read_user_entry(TRUE);
}
