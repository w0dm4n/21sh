/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 11:16:31 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/22 11:16:32 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <stdio.h>

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

char	*add_file_from_the_current_directory(char *cmd, int start, int end)
{
	cmd = del_char_in(cmd, start, end);
	cmd = add_file(opendir("."), cmd);
	return (cmd);
}

char	*get_file_extension(char *cmd, int start, int end)
{
	
}

char	*add_file_with_good_extension(char *cmd, int start, int end)
{
	char	**get_all_good_files;
	char	*get_extension;

	if (!(get_all_good_files = malloc(sizeof(char*) * MAX_LINE)))
		return (NULL);
	if (!(get_extension = malloc(sizeof(char*) * MAX_LINE)))
		return (NULL);
	get_extension = get_extension(cmd, start, end);
	cmd = del_char_in(cmd, start, end);
	return (cmd);
}

void	handle_wildcards(void)
{
	int		start;
	int		end;
	char	*wildcards;

	start = 0;
	wildcards = NULL;
	if (ft_strchr(g_cmd, '*'))
	{
		start = get_start(g_cmd);
		end = get_end(g_cmd, start);
		if (start && end && start < end)
		{
			wildcards = get_value(start, end, wildcards, g_cmd);
			if (ft_strchr(wildcards, '.'))
				g_cmd = add_file_with_good_extension(g_cmd, start, end);
			else
				g_cmd = add_file_from_the_current_directory(g_cmd, start, end);
		}
	}
}