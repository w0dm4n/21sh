/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:35:14 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/22 14:35:17 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int			get_fd_to(char *cmd, int start)
{
	char	*fd;
	int		i;

	i = 0;
	if (!(fd = malloc(sizeof(char) * 96)))
		return (0);
	while (cmd[start] && cmd[start] != ' ')
		start--;
	start++;
	while (cmd[start] && cmd[start] != '>')
	{
		fd[i] = cmd[start];
		i++;
		start++;
	}
	return (ft_atoi(fd));
}

int			get_new_fd(char *cmd, int start)
{
	char	*fd;
	int		i;

	i = 0;
	if (!(fd = malloc(sizeof(char) * 96)))
		return (0);
	while (cmd[start] && cmd[start] != '&')
		start++;
	start++;
	while (cmd[start] && cmd[start] != ' ')
	{
		fd[i] = cmd[start];
		i++;
		start++;
	}
	if (fd[0] == '-')
		return (-1);
	return (ft_atoi(fd));
}

void		dup_or_close_fd(void)
{
	int		i;
	int		position;
	int		fd_to;
	int		new_fd;

	i = 0;
	position = 0;
	while (g_cmd[i])
	{
		if (g_cmd[i] == '>' && g_cmd[i + 1] == '&')
			position = i;
		i++;
	}
	if (position)
	{
		fd_to = get_fd_to(g_cmd, position);
		new_fd = get_new_fd(g_cmd, position);
		g_fd = dup(fd_to);
		g_closed = fd_to;
		if (new_fd == -1)
			close(fd_to);
		else
			dup2(new_fd, fd_to);
	}
}
