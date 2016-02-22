/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_v.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 02:09:50 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/25 02:10:45 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*replace_env(char *env, char *new_value, int i, int i_2)
{
	char	*new;

	while (env[i] != '=')
		i++;
	i++;
	if (!(new = malloc(sizeof(char) * (ft_strlen(new_value + 1) + i))))
		return (NULL);
	ft_bzero(new, (ft_strlen(new_value + 1) + i));
	i = 0;
	while (env[i] != '=')
	{
		new[i] = env[i];
		i++;
	}
	new[i] = env[i];
	i++;
	while (new_value[i_2])
	{
		new[i] = new_value[i_2];
		i++;
		i_2++;
	}
	new[i] = '\0';
	return (new);
}

void	set_env(char *env, char *value_to_set)
{
	int		i;
	int		i_2;
	char	*tmp_char;

	if (!(tmp_char = ft_strnew(100)))
		return ;
	i = 0;
	i_2 = 0;
	while (g_env[i])
	{
		while (g_env[i][i_2])
		{
			if (g_env[i][i_2] == '=')
				break ;
			tmp_char[i_2] = g_env[i][i_2];
			i_2++;
		}
		if (!ft_strcmp(tmp_char, env))
			g_env[i] = replace_env(g_env[i], value_to_set, 0, 0);
		ft_bzero(tmp_char, 100);
		i++;
		i_2 = 0;
	}
	return ;
}

void	print_all_env(void)
{
	int		i;

	i = 0;
	while (g_env[i])
	{
		ft_putstr(g_env[i]);
		if (g_env[i + 1])
			ft_putstr("\n");
		i++;
	}
}

char	*get_env_value(char *value)
{
	int		i;
	int		i_2;
	char	*new;
	int		size;

	i = 0;
	i_2 = 0;
	while (value[i] != '=')
		i++;
	size = (ft_strlen(value) - i);
	if (!(new = (char*)malloc(sizeof(char) * size)))
		return (NULL);
	ft_bzero(new, size);
	i++;
	while (value[i])
	{
		new[i_2] = value[i];
		i++;
		i_2++;
	}
	new[i_2] = '\0';
	return (new);
}

char	*get_env(char *to_find)
{
	int		i;
	int		i_2;
	char	*tmp_char;

	if (!(tmp_char = malloc(sizeof(char) * 100)))
		return (NULL);
	ft_bzero(tmp_char, 100);
	i = 0;
	i_2 = 0;
	while (g_env[i])
	{
		while (g_env[i][i_2])
		{
			if (g_env[i][i_2] == '=')
				break ;
			tmp_char[i_2] = g_env[i][i_2];
			i_2++;
		}
		if (!ft_strcmp(tmp_char, to_find))
			return (get_env_value(g_env[i]));
		ft_bzero(tmp_char, 100);
		i++;
		i_2 = 0;
	}
	return (NULL);
}
