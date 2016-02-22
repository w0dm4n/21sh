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

char	*add_file_from_the_current_directory(char *cmd, int start, int end)
{
	cmd = del_char_in(cmd, start, end);
	cmd = add_file(opendir("."), cmd);
	return (cmd);
}

char	*get_file_extension_in_dir(char *cmd)
{
	int		i;
	int		i_2;
	char	*extension;

	i = 0;
	i_2 = 0;
	if (!(extension = malloc(sizeof(char) * MAX_LINE)))
		return (NULL);
	while (cmd[i] && cmd[i] != '.')
		i++;
	while (cmd[i] && cmd[i] != ' ')
	{
		extension[i_2] = cmd[i];
		i_2++;
		i++;
	}
	return (extension);
}

char	*add_file_with_ext(DIR *dir, char *extension, char *cmd)
{
	struct dirent	*files;
	char			*curr_ext;

	if (!(curr_ext = malloc(sizeof(char) * MAX_LINE)))
		return (NULL);
	cmd = ft_strcat(cmd, " ");
	while ((files = readdir(dir)) != NULL)
	{
		if (ft_is_all_print(files->d_name) && files->d_name[0] != '.')
		{
			curr_ext = get_file_extension_in_dir(files->d_name);
			if (!ft_strcmp(extension, curr_ext))
			{
				cmd = ft_strcat(cmd, ft_strdup(files->d_name));
				cmd = ft_strcat(cmd, " ");
			}
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
