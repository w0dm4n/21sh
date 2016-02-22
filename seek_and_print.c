/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 15:59:41 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/20 15:59:43 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		interesting(char *cmd, char *occurence, int array_len)
{
	char *extension;

	extension = get_occur_extension(occurence);
	if (!ft_strcmp(cmd, "cat") ||
		!ft_strcmp(cmd, "vim") ||
		!ft_strcmp(cmd, "emacs") ||
		!ft_strcmp(cmd, "nano") ||
		!ft_strcmp(cmd, "cat") ||
		!ft_strcmp(cmd, "more"))
	{
		if (!ft_strcmp(extension, ".c"))
			return (1);
	}
	else
	{
		if (array_len)
			return (1);
	}
	return (0);
}

void	delete_from_stdout(char *args)
{
	int		i;
	char	*res;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		g_cmd = del_in(g_cmd, g_cursor_pos);
		g_cursor_pos--;
		res = tgetstr("le", NULL);
		tputs(res, 0, move_cursor);
		i++;
	}
	res = tgetstr("ec", NULL);
	tputs(tgoto(res, 0, ft_strlen(args)), 1, move_cursor);
}

void	print_char_and_move_pos(char *to_print)
{
	int i;

	if (!to_print)
		return ;
	i = 0;
	while (to_print[i])
	{
		ft_putchar(to_print[i]);
		g_cursor_pos++;
		i++;
	}
	g_cmd = ft_strcat(g_cmd, to_print);
}

void	seek_and_print(char *cmd)
{
	char			**args;
	int				i;
	char			**all_files;
	int				size_until_dot;
	char			**a_oc;

	i = 0;
	a_oc = NULL;
	args = ft_strsplit(cmd, ' ');
	if (args[1] && !args[2])
	{
		size_until_dot = get_size(args[1]);
		all_files = get_all_files_from_current_directory(opendir("."));
		a_oc = alloc_array(all_files, a_oc);
		a_oc = get_all_occur(all_files, a_oc, args[1], size_until_dot);
		while (a_oc[i])
		{
			if (interesting(args[0], a_oc[i], ft_lenarray((void**)a_oc)))
				break ;
			i++;
		}
		delete_from_stdout(args[1]);
		print_char_and_move_pos(a_oc[i]);
	}
}
