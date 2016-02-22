/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 00:24:51 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/27 00:26:30 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		delete_var_from_env(char *to_del, int i_3, int i, int i_2)
{
	char	**new_env;
	char	*var_name;

	var_name = ft_strnew(1024);
	if (!(new_env = malloc(sizeof(char*) * MAX_VAR_ENV_SIZE)))
		return ;
	ft_bzero(new_env, MAX_VAR_ENV_SIZE);
	while (g_env[i])
	{
		while (g_env[i][i_2] != '=')
		{
			var_name[i_2] = g_env[i][i_2];
			i_2++;
		}
		if (ft_strcmp(var_name, to_del))
		{
			new_env[i_3] = ft_strdup(g_env[i]);
			i_3++;
		}
		i_2 = 0;
		ft_bzero(var_name, 1024);
		i++;
	}
	g_env = new_env;
	free(var_name);
}

int			check_if_needed(char *var)
{
	if (!ft_strcmp(var, "PATH") ||
		!ft_strcmp(var, "PWD") ||
		!ft_strcmp(var, "OLDPWD"))
	{
		ft_putstr("unsetenv: can't delete this value :(");
			return (0);
	}
	return (1);
}

void		un_set_env(char *args)
{
	int		args_nbr;
	char	**all_args;
	char	*env_content;

	if (args)
	{
		args_nbr = get_args_nbr(args);
		if (args_nbr == 1)
		{
			args = ft_strtrim(args);
			all_args = ft_strsplit(args, ' ');
			env_content = get_env(all_args[0]);
			if (env_content != NULL)
			{
				if (check_if_needed(all_args[0]))
					delete_var_from_env(all_args[0], 0, 0, 0);
			}
			else
				ft_putstr("unsetenv: can't find this value on the environment");
		}
		else
			ft_putstr("unsetenv: wrong argument (syntax: unsetenv VALUE)");
	}
	else
		ft_putstr("unsetenv: wrong argument (syntax: unsetenv VALUE)");
}
