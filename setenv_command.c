/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_or_add_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 23:42:49 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/26 23:43:55 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		add_in_env(char *var, char *content)
{
	char	**new_env;
	int		i;
	char	*to_set;

	if (!(to_set = malloc(sizeof(char) * MAX_VAR_ENV_SIZE)))
		return ;
	to_set = ft_strcat(to_set, var);
	to_set = ft_strcat(to_set, "=");
	to_set = ft_strcat(to_set, content);
	i = 0;
	while (g_env[i])
		i++;
	if (!(new_env = malloc(sizeof(char*) * MAX_VAR_ENV_SIZE)))
		return ;
	new_env = ft_set_null(new_env);
	i = 0;
	while (g_env[i])
	{
		new_env[i] = ft_strdup(g_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(to_set);
	g_env = new_env;
}

void		change_or_add_env(char *args)
{
	int		args_nbr;
	char	**all_args;
	char	*env_content;

	args_nbr = 0;
	if (args)
	{
		args_nbr = get_args_nbr(args);
		if (args_nbr == 2)
		{
			args = ft_strtrim(args);
			all_args = ft_strsplit(args, ' ');
			env_content = get_env(all_args[0]);
			if (env_content != NULL)
				set_env(all_args[0], all_args[1]);
			else
				add_in_env(all_args[0], all_args[1]);
		}
		else
			ft_putstr("setenv: wrong argument (syntax: setenv VAR VALUE).");
	}
	else
		ft_putstr("setenv: wrong argument (syntax: setenv VAR VALUE).");
}
