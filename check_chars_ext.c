/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 02:53:36 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 02:53:38 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		check_hook(char *g_cmd, int count_1, int count_2, int count_f)
{
	count_1 = count_char(g_cmd, '[');
	count_2 = count_char(g_cmd, ']');
	count_f = (count_1 + count_2);
	if ((count_f % 2) || !count_2 || !count_1)
	{
		if (count_1 > count_2 && count_1 && count_2)
			ft_putstr_fd("\nToo many ['s.", 2);
		else if (count_2 > count_1 && count_1 && count_2)
			ft_putstr_fd("\nToo many ]'s.", 2);
		else
			ft_putstr_fd("\nBadly placed []'s.", 2);
		write(1, "\n$> ", 4);
		if (g_cmd[0])
			g_logs = add_in_front(g_logs, g_cmd);
		meurs_en_enfer(g_cmd);
		return (0);
	}
	else
		return (1);
}

int		check_accolade(char *g_cmd, int count_1, int count_2, int c)
{
	count_1 = count_char(g_cmd, '{');
	count_2 = count_char(g_cmd, '}');
	c = (count_1 + count_2);
	if ((c % 2) || !count_2 || !count_1)
	{
		if (count_1 > count_2 && count_1 && count_2)
			ft_putstr_fd("\nToo many {'s.", 2);
		else if (count_2 > count_1 && count_1 && count_2)
			ft_putstr_fd("\nToo many }'s.", 2);
		else
			ft_putstr_fd("\nBadly placed {}'s.", 2);
		write(1, "\n$> ", 4);
		if (g_cmd[0])
			g_logs = add_in_front(g_logs, g_cmd);
		meurs_en_enfer(g_cmd);
		return (0);
	}
	else
		return (1);
}
