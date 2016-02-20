/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_filedescriptor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 12:26:57 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/20 12:26:58 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int		check_if_f_exist_n_perm(char *file_name)
{
	struct stat		*tmp;

	if (!(tmp = malloc(sizeof(struct stat*))))
		return (0);
	if (lstat(file_name, tmp) < 0)
	{
		ft_putstr_fd("21sh: no such file or directory: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
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

void		get_file_n_exec(char *cmd, char *file_name, char **args, int res)
{
	char	*file_content;
	int		fd;
	int		fd_dup[2];
	pid_t	pid;
	int		child;
	//int		new;		

	if (!(file_content = malloc(sizeof(char) * FILE_BUFFER)))
		return ;
	args = add_full_name(args, get_path_and_name(res, cmd));
	pipe(fd_dup);
	fd = open(file_name, O_RDONLY);
	read(fd, file_content, FILE_BUFFER);
	close(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_dup[1], 1);
		close(fd_dup[1]);
		ft_putstr(file_content);
		exit(0);
	}
	else
	{
		wait(&child);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd_dup[0], 0);
			close(fd_dup[0]);
			execve(get_path_and_name(res, cmd), args, g_env);
			exit(0);
		}
		else
		{
			wait(&child);
			// FIND A FUCKING WAY FOR CLOSE THE CHILD
			//sleep(1);
		}
	}
}

void			exec_with_filedescriptor(char *cmd, int nbr, char to_find)
{
	char	*cmd_to_exe;
	char	*file;
	char	**args;
	int		res;
	int		permissions;

	res = 0;
	permissions = 0;
	cmd_to_exe = get_separated_by_char(cmd, to_find, 0, nbr);
	file = get_separated_by_char(cmd, to_find, 1, nbr);
	args = get_cmd_args(ft_strsplit(cmd_to_exe, ' '), ft_strsplit(file, ' '));
	if (!(res = check_cmd_n_file(cmd_to_exe, file, res)))
		return ;
	else if (!(permissions = check_if_f_exist_n_perm(get_only_name(file))))
		return ;
	if (nbr == 1)
		get_file_n_exec(get_only_name(cmd_to_exe), get_only_name(file), args, res);
}
