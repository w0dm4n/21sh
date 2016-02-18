/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_separated_by_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 04:41:18 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/18 04:41:19 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*get_before(char *cmd, char to_find, int nbr, char *new_cmd)
{
	int	i;
	int	occ;

	i = 0;
	occ = 0;
	while (cmd[i])
	{
		if (cmd[i] == to_find)
			occ++;
		if (occ == nbr)
			break ;
		new_cmd[i] = cmd[i];
		i++;
	}
	if (nbr == 2)
		new_cmd[i - 1] = '\0';
	else
		new_cmd[i] = '\0';
	return (new_cmd);
}

char	*get_separated_by_char(char *cmd, char to_find, int pos, int nbr)
{
	char	*new_cmd;
	int		i;

	i = 0;
	if (!(new_cmd = malloc(sizeof(char) * READ_BUFFER)))
		return (NULL);
	if (!pos)
		new_cmd = get_before(cmd, to_find, nbr, new_cmd);
	//else
	//	new_cmd = get_after(cmd, to_find, nbr);
	return (new_cmd);
}
