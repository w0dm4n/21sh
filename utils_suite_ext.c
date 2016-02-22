/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_suite_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 10:52:08 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/22 10:52:10 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		ft_is_all_print(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '.' && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int		ft_is_one_printable(char *str)
{
	int i;
	int how_much;

	i = 0;
	how_much = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '.' || str[i] == '_')
			how_much++;
		i++;
	}
	return (how_much);
}
