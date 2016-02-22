/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 03:15:16 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/09 03:15:27 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*update_cmd(char *real_cmd, char *to_add)
{
	char	*tmp;
	int		i;
	int		i_2;

	i = 0;
	i_2 = 0;
	if (!(tmp = malloc(sizeof(char) * READ_BUFFER)))
		return (NULL);
	while (real_cmd[i])
	{
		tmp[i] = real_cmd[i];
		i++;
	}
	while (to_add[i_2])
	{
		if (to_add[i_2] == '\\')
			break ;
		tmp[i] = to_add[i_2];
		i++;
		i_2++;
	}
	tmp[i] = '\0';
	free(real_cmd);
	return (tmp);
}

char	*get_multi_line_cmd(char *g_cmd)
{
	int		i;
	char	*real_cmd;

	if (!(real_cmd = malloc(sizeof(char) * READ_BUFFER)))
		return (NULL);
	i = 0;
	while (i <= g_multi_line)
	{
		real_cmd = update_cmd(real_cmd, g_multi_line_data[i]);
		free(g_multi_line_data[i]);
		i++;
	}
	free(g_cmd);
	g_cmd = ft_strdup(real_cmd);
	g_multi_line = 0;
	handle_all_cmds(g_cmd);
	return (g_cmd);
}

void	handle_multi_line_cmd(void)
{
	g_new_cmd = FALSE;
	g_cursor_pos = 0;
	ft_putstr_fd(COLOR_RED, 1);
	ft_putstr_fd("\n\\ ", 1);
	ft_putstr_fd(DEFAULT_COLOR, 1);
	g_multi_line_data[g_multi_line] = ft_strdup(g_cmd);
	g_cmd = meurs_en_enfer(g_cmd);
	g_multi_line++;
}
