/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_all_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 01:48:01 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/17 01:48:02 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		pipe_number(char *str, int i)
{
	int pipe_number;

	pipe_number = 0;
	while (str[i])
	{
		if (str[i] == '|')
			pipe_number++;
		i++;
	}
	return (pipe_number);
}

void	handle_all_cmds_suite(char *cmd)
{
	int		i;
	int		pipe_nbr;
	char	**cmd_pipe;
	int		fd[2];
	pid_t	pid;
	int		what_to_do;

	pipe(fd);
	i = 0;
	what_to_do = 0;
	pipe_nbr = pipe_number(cmd, 0);
	if (pipe_nbr)
	{
		cmd_pipe = ft_strsplit(cmd, '|');
		while (cmd_pipe[i])
		{
			if (!what_to_do)
			{
				pid = fork();
				if (pid == 0)
				{
					dup2(fd[1], 1);
					close(fd[1]);
					handle_special_case(cmd_pipe[i]);
				}
				what_to_do++;
			}
			else
			{
				pid = fork();
				if (pid == 0)
				{
					dup2(fd[0], 0);
					close(fd[0]);
					handle_special_case(cmd_pipe[i]);
				}
				what_to_do = 0;
			}
			i++;
		}
	}
	else
		handle_special_case(cmd);
}

void	handle_all_cmds(char *buffer)
{
	char	**command_nbr;
	int		array_size;
	int		i;

	i = 0;
	if (!buffer)
		return ;
	if (!buffer[0] || !ft_strlen(buffer))
		return ;
	buffer = ft_strtrim(buffer);
	command_nbr = ft_strsplit(buffer, ';');
	array_size = ft_lenarray((void**)command_nbr);
	while (i < array_size && command_nbr[i])
	{
		handle_all_cmds_suite(command_nbr[i]);
		(command_nbr[i + 1] ? ft_putstr("\n") : (i = array_size));
		i++;
	}
}
