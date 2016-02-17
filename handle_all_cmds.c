/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_all_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 01:48:01 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/17 01:48:02 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	handle_all_cmds(char *buffer)
{
	char	**command_nbr;
	int		array_size;
	int		i;

	i = 0;
	buffer = ft_strtrim(buffer);
	command_nbr = ft_strsplit(buffer, ';');
	array_size = ft_lenarray((void**)command_nbr);
	while (i < array_size)
	{
		i++;
	}
}
