/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 00:50:58 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/25 00:54:32 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*get_subdir(char *path)
{
	int		i;
	char	*new_path;
	int		i_2;

	i = ft_strlen(path);
	i_2 = 0;
	if (!(new_path = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (path[i] != '/')
		i--;
	i--;
	while (i_2 <= i)
	{
		new_path[i_2] = path[i_2];
		i_2++;
	}
	new_path[i_2] = '\0';
	if (!new_path[0])
		return ("/");
	return (new_path);
}

void		change_folder(char *path, int change_path)
{
	char	*old_pwd;

	old_pwd = get_env("PWD");
	if (change_path)
		chdir(path);
	set_env("PWD", path);
	set_env("OLDPWD", old_pwd);
}

int			get_args_nbr(char *args)
{
	int i;
	int	nbr_args;

	i = 0;
	nbr_args = 0;
	while (args[i])
	{
		if (args[i] == ' ')
			nbr_args++;
		i++;
	}
	return (nbr_args);
}

void		chdir_command(char *args)
{
	char	*path;

	if (!(path = (char*)malloc(sizeof(char) * READ_BUFFER)))
		return ;
	if (!args || !ft_strcmp(args, " ~"))
	{
		if (get_path(get_env("HOME"), NULL))
			change_folder(get_env("HOME"), 1);
	}
	else
		chdir_command_ext(args, path, 0);
	free(args);
	free(path);
}
