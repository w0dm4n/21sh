/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 22:50:27 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/08 10:57:05 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		do_cmd(char *cmd, char *cmd_args, int res)
{
	if (!ft_strcmp(cmd, "cd"))
		chdir_command(cmd_args);
	else if (!ft_strcmp(cmd, "whoami"))
		ft_putstr(get_env("USER"));
	else if (!ft_strcmp(cmd, "pwd"))
		ft_putstr(get_env("PWD"));
	else if (!ft_strcmp(cmd, "env"))
		print_all_env();
	else if (!ft_strcmp(cmd, "setenv"))
		change_or_add_env(cmd_args);
	else if (!ft_strcmp(cmd, "unsetenv"))
		un_set_env(cmd_args);
	else if (cmd[0] == '.' && cmd[1] == '/')
		execute_binary_from_current_folder(cmd, cmd_args);
	else if (cmd[0] == '/')
		execute_from_asked_dir(cmd, g_env, cmd_args);
	else
		execute_binary(cmd, cmd_args, g_env, res);
}
