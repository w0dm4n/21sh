/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_array_ext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 02:17:27 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 02:17:29 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	**alloc_cmd(char **current_cmd)
{
	if (!(current_cmd = malloc(sizeof(char*) * LOGS_BUFFER)))
		return (NULL);
	current_cmd = ft_set_null(current_cmd);
	return (current_cmd);
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
