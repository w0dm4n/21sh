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

char	*get_separated_by_char(char *cmd, char to_find, int pos)
{
	char	*new_cmd;
	int		i;

	i = 0;
	if (!(new_cmd = malloc(sizeof(char) * READ_BUFFER)))
		return (NULL);
	while (cmd[i] && cmd[i] != to_find)
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	new_cmd[i] = '\0';
	return (new_cmd);
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
	return (nbr);
}

void	handle_special_case(char *cmd)
{
	if (count_char_number(cmd, '>')) // write on file (overwriting if one add if two)
	{
		if (count_char_number(cmd, '>') <= 2)
			handle_cmd(cmd);
		else
			ft_putstr_fd("21sh: parse error near `>'\n", 2);
	}
	else if (count_char_number(cmd, '<')) // sending file fd to the cmd stdin
	{
		if (count_char_number(cmd, '<') <= 2)
			handle_cmd(cmd);
		else
			ft_putstr_fd("21sh: parse error near `<'\n", 2);
	}
	else
		handle_cmd(cmd);
}