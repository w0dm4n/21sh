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

void		overwrite_in_suite(char *buffer, char *file, int *fd)
{
	int		file_fd;

	read(fd[0], buffer, FILE_BUFFER);
	file_fd = open(file, O_RDWR);
	write(file_fd, buffer, ft_strlen(buffer));
	close(file_fd);
	handle_cmd(get_delete_cmd(file));
	file_fd = open(file, O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	close(file_fd);
	file_fd = open(file, O_RDWR);
	write(file_fd, buffer, ft_strlen(buffer));
	close(file_fd);
	ft_bzero(buffer, FILE_BUFFER);
}

void		overwrite_in(char *cmd, char *file, char **args, int res)
{
	int		fd[2];
	pid_t	pid;
	char	buffer[FILE_BUFFER];
	int		child_status;

	args = add_file_name(args, get_path_and_name(res, cmd));
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		execve(get_path_and_name(res, cmd), args, g_env);
	}
	else
	{
		wait(&child_status);
		overwrite_in_suite(buffer, file, fd);
	}
}

void		add_in_file_suite(char *buffer, char *buffer_2, char *file, int *fd)
{
	int file_fd;

	file_fd = open(file, O_RDONLY);
	read(file_fd, buffer, FILE_BUFFER);
	close(file_fd);
	handle_cmd(get_delete_cmd(file));
	read(fd[0], buffer_2, FILE_BUFFER);
	buffer = ft_strcat(buffer, buffer_2);
	file_fd = open(file, O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	close(file_fd);
	file_fd = open(file, O_RDWR);
	write(file_fd, buffer, ft_strlen(buffer));
	close(file_fd);
	ft_bzero(buffer, FILE_BUFFER);
	ft_bzero(buffer_2, FILE_BUFFER);
}

void		add_in_file(char *cmd, char *file, char **args, int res)
{
	int		fd[2];
	pid_t	pid;
	char	*buffer;
	char	*buffer_2;
	int		child_status;

	if (!(buffer = ft_strnew(FILE_BUFFER)))
		return ;
	if (!(buffer_2 = ft_strnew(FILE_BUFFER)))
		return ;
	args = add_file_name(args, get_path_and_name(res, cmd));
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		execve(get_path_and_name(res, cmd), args, g_env);
	}
	else
	{
		wait(&child_status);
		add_in_file_suite(buffer, buffer_2, file, fd);
	}
}

void		write_in_filedescriptor(char *cmd, int nbr, char to_find)
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
	if ((res = check_cmd(get_only_name(cmd_to_exe))) < 0)
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
		if (!(open(get_only_name(file), O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)))
			ft_putstr_fd("21sh: Can't create asked file\n", 2);
	if (nbr == 1)
		overwrite_in(get_only_name(cmd_to_exe), get_only_name(file), args, res);
	else if (nbr == 2)
		add_in_file(get_only_name(cmd_to_exe), get_only_name(file), args, res);
}
