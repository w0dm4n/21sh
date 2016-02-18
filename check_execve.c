/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 03:23:38 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/26 03:25:09 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		check_stat(char *full_path, int print)
{
	struct stat		*file_stat;

	if (!(file_stat = malloc(sizeof(struct stat*))))
		return (-1);
	if (lstat(full_path, file_stat) < 0)
	{
		if (print == 1)
			ft_putstr("executable not found !");
		return (0);
	}
	if (S_ISDIR(file_stat->st_mode))
	{
		ft_putstr("executable set is a directory !");
		return (0);
	}
	else if (!file_stat->st_mode & S_IXUSR)
	{
		ft_putstr("access denied on the executable :(");
		return (0);
	}
	return (1);
}

int		check_file(char *file, char *path)
{
	char	*full_path;
	int		size;

	size = ((ft_strlen(file) + 1) + (ft_strlen(path) + 1));
	if (!(full_path = malloc(sizeof(char) * size)))
		return (-1);
	full_path = ft_strcat(full_path, path);
	full_path = ft_strcat(full_path, "/");
	full_path = ft_strcat(full_path, file);
	if (check_stat(full_path, 0))
		return (1);
	ft_bzero(full_path, size);
	return (-1);
}

int		check_execve(char *file_name, char *all_path)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_strsplit(all_path, ':');
	while (path[i])
	{
		if (check_file(file_name, path[i]) > 0)
			return (i);
		i++;
	}
	return (-1);
}
