/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 02:20:01 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 02:20:06 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		print_color_n_prompt(void)
{
	ft_putstr(COLOR_WHITE);
	ft_putstr("$> ");
}

int			get_ascii_value(char *buff)
{
	int i;
	int ascii_value;

	i = 0;
	ascii_value = 0;
	while (buff[i])
	{
		ascii_value += buff[i];
		i++;
	}
	return (ascii_value);
}

void		free_argv(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (argv[i])
			free(argv[i]);
		i++;
	}
	free(argv);
}

char		**set_argv(char **argv, char *name)
{
	if (!argv)
	{
		if (!(argv = malloc(sizeof(char*) * 1)))
			return (NULL);
		argv[0] = get_name(name);
	}
	return (argv);
}

void		do_ls_f(void)
{
	ft_putstr_fd("\n", 1);
	g_cmd = meurs_en_enfer(g_cmd);
	g_cmd = ft_strdup("ls -F");
	g_new_cmd = 1;
}
