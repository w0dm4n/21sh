/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_filedescriptor_suite.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 04:05:16 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/19 04:05:26 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		**get_cmd_args(char **args_before, char **args_after)
{
	int		i;
	int		args_i;
	char	**args;

	i = 1;
	args_i = 0;
	if (!(args = malloc(sizeof(char*) * MAX_ARGV_SIZE)))
		return (NULL);
	args = ft_set_null(args);
	if (args_before)
	{
		while (args_before[i])
		{
			args[args_i] = ft_strdup(args_before[i]);
			i++;
			args_i++;
		}
	}
	i = 1;
	if (args_after)
		args = get_args_after(args, args_after, i, args_i);
	args[args_i] = NULL;
	return (args);
}

char		*get_only_name(char *cmd_to_exec)
{
	int		i;
	char	*name;

	if (!cmd_to_exec)
		return (NULL);
	i = 0;
	if (!(name = malloc(sizeof(char) * MAX_EXE_NAME)))
		return (NULL);
	while (cmd_to_exec[i] && cmd_to_exec[i] != ' ')
	{
		name[i] = cmd_to_exec[i];
		i++;
	}
	return (name);
}

int			check_permissons_file(char *file_name)
{
	struct stat		*tmp;

	if (!(tmp = malloc(sizeof(struct stat*))))
		return (0);
	if (lstat(file_name, tmp) < 0)
		return (2);
	if (tmp->st_mode & S_IRUSR)
		return (1);
	else
	{
		ft_putstr_fd("21sh: permission denied: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
}

char		*get_path_and_name(int res, char *cmd)
{
	char	**all_path;
	int		i;
	char	*executable_full_path;

	i = 0;
	all_path = ft_strsplit(get_env("PATH"), ':');
	while (all_path[i])
	{
		if (i == res)
			break ;
		i++;
	}
	if (!(executable_full_path = malloc(sizeof(char) * READ_BUFFER)))
		return (NULL);
	executable_full_path = ft_strcat(executable_full_path, all_path[i]);
	executable_full_path = ft_strcat(executable_full_path, "/");
	executable_full_path = ft_strcat(executable_full_path, cmd);
	return (executable_full_path);
}

char		*get_delete_cmd(char *file_name)
{
	char	*delete_cmd;

	if (!(delete_cmd = ft_strnew(MAX_EXE_NAME)))
		return (NULL);
	delete_cmd[0] = '\0';
	delete_cmd = ft_strcat(delete_cmd, "rm -rf ");
	delete_cmd = ft_strcat(delete_cmd, file_name);
	return (delete_cmd);
}
