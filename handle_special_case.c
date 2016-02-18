/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 04:25:51 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/18 04:25:54 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	count_char_number(char *str, char to_count)
{
	int i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] == to_count)
			nbr++;
		i++;
	}
	return (nbr);
}

void	handle_special_case(char *cmd)
{
	if (count_char_number(cmd, '>'))
	{
		if (count_char_number(cmd, '>') =< 2)
			handle_cmd(cmd);
		else
			ft_putstr_fd("21sh: parse error near `>'", 2);
	}
	else 
		handle_cmd(cmd);
}