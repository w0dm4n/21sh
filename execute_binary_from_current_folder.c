/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary_from_current_folder.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 14:04:02 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/28 14:05:50 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*get_exe_name(char *exe, int i_2)
{
	char	*tmp;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(exe + 1);
	if (!(tmp = malloc(sizeof(char) * size)))
		return (NULL);
	while (exe[i])
	{
		if (exe[i] != '.' && exe[i] != '/')
		{
			tmp[i_2] = exe[i];
			i_2++;
		}
		i++;
	}
	tmp[i_2] = '\0';
	return (tmp);
}

void		execute_binary_from_current_folder(char *exe, char *args)
{
	char	*current_path;
	char	*exe_name;

	exe_name = NULL;
	if (!(current_path = malloc(sizeof(char) * READ_BUFFER)))
		return ;
	getcwd(current_path, READ_BUFFER);
	current_path = ft_strcat(current_path, "/");
	if (exe)
	{
		exe_name = get_exe_name(exe, 0);
		current_path = ft_strcat(current_path, exe_name);
	}
	if (check_stat(current_path, 1))
	{
		ft_bzero(current_path, READ_BUFFER);
		getcwd(current_path, READ_BUFFER);
		launch_process(current_path, exe_name, args, g_env);
	}
}
