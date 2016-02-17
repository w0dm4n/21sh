/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 02:18:46 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 02:18:47 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		check_simple_quote(char *g_cmd, int count)
{
	count = count_char(g_cmd, '\'');
	if ((count % 2))
	{
		ft_putstr_fd("\nUnmatched '.", 2);
		write(1, "\n$> ", 4);
		if (g_cmd[0])
			g_logs = add_in_front(g_logs, g_cmd);
		meurs_en_enfer(g_cmd);
		return (0);
	}
	else
		return (1);
}

int		check_double_quote(char *g_cmd, int count)
{
	count = count_char(g_cmd, '"');
	if ((count % 2))
	{
		ft_putstr_fd("\nUnmatched \".", 2);
		write(1, "\n$> ", 4);
		if (g_cmd[0])
			g_logs = add_in_front(g_logs, g_cmd);
		meurs_en_enfer(g_cmd);
		return (0);
	}
	else
		return (1);
}

int		check_back_quote(char *g_cmd, int count)
{
	count = count_char(g_cmd, '`');
	if ((count % 2))
	{
		ft_putstr_fd("\nUnmatched `.", 2);
		write(1, "\n$> ", 4);
		if (g_cmd[0])
			g_logs = add_in_front(g_logs, g_cmd);
		meurs_en_enfer(g_cmd);
		return (0);
	}
	else
		return (1);
}

int		check_parenthese(char *g_cmd, int count_1, int count_2, int count_f)
{
	count_1 = count_char(g_cmd, '(');
	count_2 = count_char(g_cmd, ')');
	count_f = (count_1 + count_2);
	if ((count_f % 2) || !count_2 || !count_1)
	{
		if (count_1 > count_2 && count_1 && count_2)
			ft_putstr_fd("\nToo many ('s.", 2);
		else if (count_2 > count_1 && count_1 && count_2)
			ft_putstr_fd("\nToo many )'s.", 2);
		else
			ft_putstr_fd("\nBadly placed ()'s.", 2);
		write(1, "\n$> ", 4);
		if (g_cmd[0])
			g_logs = add_in_front(g_logs, g_cmd);
		meurs_en_enfer(g_cmd);
		return (0);
	}
	else
		return (1);
}

int		check_special_chars(char *g_cmd)
{
	if (ft_strchr(g_cmd, '\''))
		return (check_simple_quote(g_cmd, 0));
	if (ft_strchr(g_cmd, '"'))
		return (check_double_quote(g_cmd, 0));
	if (ft_strchr(g_cmd, '`'))
		return (check_back_quote(g_cmd, 0));
	if (ft_strchr(g_cmd, '(') || ft_strchr(g_cmd, ')'))
		return (check_parenthese(g_cmd, 0, 0, 0));
	if (ft_strchr(g_cmd, '[') || ft_strchr(g_cmd, ']'))
		return (check_hook(g_cmd, 0, 0, 0));
	if (ft_strchr(g_cmd, '{') || ft_strchr(g_cmd, '}'))
		return (check_accolade(g_cmd, 0, 0, 0));
	return (1);
}
