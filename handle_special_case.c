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

int		check_position(char *str, char to_count, int nbr)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == to_count && str[i + 1] == to_count)
			return (nbr);
		i++;
	}
	return (3);
}

int		count_char_number(char *str, char to_count)
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
	if (nbr == 2)
		nbr = check_position(str, to_count, nbr);
	return (nbr);
}

void	handle_special_case(char *cmd)
{
	if (count_char_number(cmd, '>'))
	{
		if (count_char_number(cmd, '>') <= 2)
			write_in_filedescriptor(cmd, count_char_number(cmd, '>'), '>');
		else
			ft_putstr_fd("21sh: parse error near `>'\n", 2);
	}
	else if (count_char_number(cmd, '<'))
	{
		if (count_char_number(cmd, '<') <= 2)
			exec_with_filedescriptor(cmd, count_char_number(cmd, '<'), '<');
		else
			ft_putstr_fd("21sh: parse error near `<'\n", 2);
	}
	else
		handle_cmd(cmd);
}
