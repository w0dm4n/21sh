/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_and_print_suite.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 17:38:28 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/20 17:38:30 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	**get_all_files_from_current_directory(DIR *dir)
{
	char			**tmp;
	struct dirent	*files;
	int				i;

	i = 0;
	if (!(tmp = malloc(sizeof(char) * READ_BUFFER)))
		return (NULL);
	while ((files = readdir(dir)) != NULL)
	{
		tmp[i] = ft_strdup(files->d_name);
		i++;
	}
	return (tmp);
}

int		get_size(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	return (i);
}

char	**alloc_array(char **array, char **to_alloc)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	if (!(to_alloc = malloc(sizeof(char*) * i)))
		return (NULL);
	return (to_alloc);
}

char	**get_all_occur(char **array, char **all_occur, char *to_cmd, int size)
{
	int	i;
	int	i_2;

	i = 0;
	i_2 = 0;
	while (array[i])
	{
		if (!ft_strncmp(to_cmd, array[i], size))
		{
			all_occur[i_2] = ft_strdup(array[i]);
			i_2++;
		}
		i++;
	}
	free(array);
	return (all_occur);
}

char	*get_occur_extension(char *occur)
{
	int		i;
	int		i_2;
	char	*tmp;

	i = get_size(occur);
	i_2 = 0;
	if (!(tmp = malloc(sizeof(char) * i)))
		return (NULL);
	while (occur[i])
	{
		tmp[i_2] = occur[i];
		i++;
		i_2++;
	}
	return (tmp);
}
