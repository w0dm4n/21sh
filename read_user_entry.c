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

char		*read_entry(char *buff)
{
	struct termios *term;
	int 			ascii_value;
	int				i;

	ascii_value = 0;
	i = 0;
	if (!(term = malloc(sizeof(struct termios))))
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
	return (buff);
}

void		print_color_n_prompt(void)
{
	ft_putstr(COLOR_WHITE);
	ft_putstr("$> ");
}

void		read_user_entry(void)
{
	char	*buffer;

	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFFER)))
		return ;
	//print_color_n_prompt();
	buffer = read_entry(buffer);
	// if ret = 1 handle cmd -> prompt again 
	ft_bzero(buffer, READ_BUFFER);
	read_user_entry();
}
