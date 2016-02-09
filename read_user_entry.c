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

void		print_color_n_prompt(void)
{
	ft_putstr(COLOR_WHITE);
	ft_putstr("$>");
}

void		read_user_entry(void)
{
	char	*buffer;

	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFFER)))
		return ;
	print_color_n_prompt();
	read(0, buffer, READ_BUFFER);
	ft_bzero(buffer, READ_BUFFER);
	read_user_entry();
}
