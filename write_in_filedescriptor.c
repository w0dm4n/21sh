/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_filedescriptor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 04:49:07 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/18 04:49:08 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static char		**get_cmd_args(char **args_before, char **args_after)
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
	{
		while (args_after[i])
		{
			args[args_i] = ft_strdup(args_after[i]);
			i++;
			args_i++;
		}
	}
	args[args_i] = NULL;
	return (args);
}

char			*get_only_name(char *cmd_to_exec)
{
	int		i;
	char	*name;

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

int				check_permissons_file(char *file_name)
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

char			*get_path_and_name(int res, char *cmd)
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

void			overwrite_in(char *cmd, char *file, char **args, int res)
{
	int		fd[2];
	pid_t	pid;
	char	tamer[40096];

	args = add_file_name(args, get_path_and_name(res, cmd)); // update exe name unset ./
	/*int i = 0;
	while (args[i])
	{
		ft_putstr(args[i]);
		ft_putstr("\n");
		i++;
	}*/
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		execve(get_path_and_name(res, cmd), args, g_env);
	}
	read(fd[0], tamer, 40096);
	int test;

	test = open(file, O_RDWR);
	write(test, tamer, ft_strlen(tamer));
	ft_bzero(tamer, 40096);
}

void			write_in_filedescriptor(char *cmd, int nbr, char to_find)
{
	char	*cmd_to_exec;
	char	*file;
	char	**args;
	int		res;
	int		permissions;

	res = 0;
	permissions = 0;
	cmd_to_exec = get_separated_by_char(cmd, to_find, 0, nbr);
	file = get_separated_by_char(cmd, to_find, 1, nbr);
	args = get_cmd_args(ft_strsplit(cmd_to_exec, ' '), ft_strsplit(file, ' '));
	if ((res = check_cmd(get_only_name(cmd_to_exec))) < 0)
	{
		ft_putstr_fd("\n", 2);
		return ;
	}
	else if (!file)
	{
		ft_putstr_fd("21sh: parse error near ", 2);
		write(2, "`\\", 2);
		write(2, "n'", 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	else if (!(permissions = check_permissons_file(get_only_name(file))))
		return ;
	if (permissions == 2)
	{
		if (!(open(get_only_name(file), O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)))
			ft_putstr_fd("21sh: Can't create asked file\n", 2);
	}
	if (nbr == 1)
		overwrite_in(get_only_name(cmd_to_exec), get_only_name(file), args, res);
	//else if (nbr == 2)
	//	ft_putstr("add in");
}