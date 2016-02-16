/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 02:20:01 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 02:20:06 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		print_color_n_prompt(void)
{
	ft_putstr(COLOR_WHITE);
	ft_putstr("$> ");
}

int			get_ascii_value(char *buff)
{
	int i;
	int ascii_value;

	i = 0;
	ascii_value = 0;
	while (buff[i])
	{
		ascii_value += buff[i];
		i++;
	}
	return (ascii_value);
}