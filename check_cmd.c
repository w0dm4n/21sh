/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 22:49:11 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/08 10:56:03 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		check_cmd(char *cmd)
{
	int res;

	res = 0;
	if (!ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "setenv") ||
		!ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "exit") ||
		!ft_strcmp(cmd, "whoami") ||
		!ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "unsetenv")
		|| (cmd[0] == '.' && cmd[1] == '/')
		|| cmd[0] == '/')
		return (1);
	else if ((res = check_execve(cmd, get_env("PATH"))) >= 0)
		return (res);
	else if (res < 0)
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(cmd);
		return (-1);
	}
	return (-1);
}
