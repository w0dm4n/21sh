/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access_folder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 00:54:39 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/26 00:54:46 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char			*try_hidden_folder(char *path, int i, int i_2, char *new)
{
	char	*file_name;

	if (!(new = malloc(sizeof(char) * PATH_MAX_SIZE)))
		return (NULL);
	if (!(file_name = malloc(sizeof(char) * 1024)))
		return (NULL);
	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	while (i_2 < i)
	{
		new[i_2] = path[i_2];
		i_2++;
	}
	i_2 = 0;
	i++;
	while (path[i])
	{
		file_name[i_2] = path[i];
		i_2++;
		i++;
	}
	new = ft_strcat(new, "/.");
	new = ft_strcat(new, file_name);
	return (new);
}

struct stat		*get_folder_stat(char *path, struct stat *file_stat)
{
	struct stat		*tmp;

	file_stat = NULL;
	if (!(tmp = malloc(sizeof(struct stat*))))
		return (NULL);
	if (lstat(path, tmp) < 0)
	{
		path = try_hidden_folder(path, 0, 0, NULL);
		if (lstat(path, tmp) < 0)
			return (NULL);
	}
	return (tmp);
}

int				check_if_readable(struct stat *file_stat, char *args)
{
	if (file_stat->st_mode & S_IRUSR)
		return (1);
	else
	{
		ft_putstr("cd: permission denied: ");
		ft_putstr(args);
		return (0);
	}
}

int				check_access_folder(char *real_path, char *args)
{
	struct stat		*file_stat;

	file_stat = NULL;
	if (!(file_stat = get_folder_stat(real_path, file_stat)))
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(args);
		return (0);
	}
	else if (!S_ISDIR(file_stat->st_mode))
	{
		ft_putstr("cd: not a directory: ");
		ft_putstr(args);
		return (0);
	}
	return ((check_if_readable(file_stat, args)) ? 1 : 0);
	free(file_stat);
}
