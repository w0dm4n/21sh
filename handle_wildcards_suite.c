/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards_suite.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 12:51:08 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/22 12:51:15 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		get_start(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != '*')
		i++;
	return (i);
}

int		get_end(char *cmd, int start)
{
	while (cmd[start] && cmd[start] != ' ')
		start++;
	return (start);
}

char	*get_value(int start, int end, char *wildcards, char *cmd)
{
	int	size;
	int	i;

	i = 0;
	size = ((end - start) + 1);
	if (!(wildcards = malloc(sizeof(char) * size)))
		return (NULL);
	while (start <= end)
	{
		wildcards[i] = cmd[start];
		start++;
		i++;
	}
	wildcards[i] = '\0';
	return (wildcards);
}

char	*add_file(DIR *dir, char *cmd)
{
	struct dirent	*files;

	cmd = ft_strcat(cmd, " ");
	while ((files = readdir(dir)) != NULL)
	{
		if (ft_is_all_print(files->d_name) && files->d_name[0] != '.')
		{
			cmd = ft_strcat(cmd, ft_strdup(files->d_name));
			cmd = ft_strcat(cmd, " ");
		}
	}
	return (cmd);
}

char	*del_char_in(char *cmd, int start, int end)
{
	char	*get_cmd;
	int		i;

	i = 0;
	if (!(get_cmd = malloc(sizeof(char) * READ_BUFFER)))
		return (NULL);
	while (i < start)
	{
		get_cmd[i] = cmd[i];
		i++;
	}
	while (cmd[end])
	{
		get_cmd[i] = cmd[end];
		i++;
		end++;
	}
	return (get_cmd);
}
