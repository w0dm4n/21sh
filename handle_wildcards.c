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
	char	*file_extension;
	int		size;
	int		i;

	i = 0;
	size = ((end - start) + 1);
	if (!(file_extension = malloc(sizeof(char) * size)))
		return (NULL);
	while (cmd[start] && cmd[start] != '.')
		start++;
	while (start <= end && cmd[start])
	{
		file_extension[i] = cmd[start];
		i++;
		start++;
	}
	return (file_extension);
}

char	*add_file_with_ext(DIR *dir, char *extension, char *cmd)
{
	struct dirent	*files;
	char			*curr_ext;

	extension = NULL;
	if (!(curr_ext = malloc(sizeof(char) * MAX_LINE)))
		return (NULL);
	cmd = ft_strcat(cmd, " ");
	while ((files = readdir(dir)) != NULL)
	{
		if (ft_is_all_print(files->d_name) && files->d_name[0] != '.')
		{
			curr_ext = get_file_extension(files->d_name, 0, ft_strlen(files->d_name));
			ft_putstr(curr_ext);
			/*if (!ft_strcmp(extension, curr_ext))
			{
				cmd = ft_strcat(cmd, ft_strdup(files->d_name));
				cmd = ft_strcat(cmd, " ");
			}*/
			ft_bzero(curr_ext, MAX_LINE);
		}
	}
	free(curr_ext);
	return (cmd);
}


char	*add_file_with_good_extension(char *cmd, int start, int end)
{
	char	*extension;

	extension = get_file_extension(cmd, start, end);
	cmd = del_char_in(cmd, start, end);
	cmd = add_file_with_ext(opendir("."), extension, cmd);
	//ft_putstr(cmd);
	exit(0);
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