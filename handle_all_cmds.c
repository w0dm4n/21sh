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
	int		pipe;
	char	**cmd_pipe;

	i = 0;
	pipe = pipe_number(cmd, 0);
	cmd_pipe = ft_strsplit(cmd, '|');
	while (cmd_pipe[i])
	{
		ft_putstr(cmd_pipe[i]);
		i++;
	}
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
