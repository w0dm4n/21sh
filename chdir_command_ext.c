/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_command_ext.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 03:58:26 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/27 03:58:32 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	chdir_command_ext(char *args, char *path, int args_nbr)
{
	args_nbr = get_args_nbr(args);
	args = ft_strtrim(args);
	if (args_nbr == 1)
	{
		if (!ft_strcmp(args, "-"))
			change_folder(get_env("OLDPWD"), 1);
		else
		{
			if (!ft_strcmp(args, "/"))
				change_folder("/", 1);
			if (!ft_strcmp(args, ".") || !ft_strcmp(args, "./"))
				return ;
			if (get_path(get_env("PWD"), args))
			{
				chdir(args);
				getcwd(path, READ_BUFFER);
				change_folder(path, 0);
			}
		}
	}
	else
		ft_putstr("cd: too many arguments");
}
