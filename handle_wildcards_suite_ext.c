/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards_suite_ext.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 12:54:00 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/22 12:54:01 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*get_file_extension(char *cmd, int start, int end)
{
	char	*file_extension;
	int		size;
	int		i;

	i = 0;
	size = ((end - start) + 1);
	if (!(file_extension = malloc(sizeof(char) * size)))
		return (NULL);
	while (cmd[start] && cmd[start] != '.')
		start++;
	while (start <= end && cmd[start])
	{
		file_extension[i] = cmd[start];
		i++;
		start++;
	}
	return (file_extension);
}
