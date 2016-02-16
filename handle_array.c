/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 02:11:37 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 02:11:38 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*get_args(char *buffer, int i, int i_2)
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

char		*get_real_cmd(char *buffer, int i, int res, char *get_cmd)
{
	char	*cmdnargs;
	int		pos;

	i = 0;
	res = 0;
	cmdnargs = NULL;
	buffer = ft_strtrim(buffer);
	pos = ft_strposition(buffer, " ");
	if (pos && ((cmdnargs = ft_strnew(READ_BUFFER))))
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

char		**add_in_front(char **logs, char *cmd)
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

char		*add_in(char *g_cmd, int pos, char *toadd, int i)
{
	char	*new_cmd;
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
	g_cmd = meurs_en_enfer(g_cmd);
	new_cmd[i] = '\0';
	return (new_cmd);
}

char		*get_new_cmdncopy(char *g_cmd, int *selected_pos)
{
	char	*tmp;
	int		i;
	int		i_2;

	i = 0;
	i_2 = 0;
	if (!(tmp = malloc(sizeof(char) * READ_BUFFER)))
		return (NULL);
	while (i <= READ_BUFFER)
	{
		if (selected_pos[i])
		{
			tmp[i_2] = g_cmd[i];
			i_2++;
			g_cursor_pos++;
		}
		i++;
	}
	tmp[i_2] = '\0';
	ft_putstr(tmp);
	g_cmd = ft_strcat(g_cmd, tmp);
	return (g_cmd);
}
