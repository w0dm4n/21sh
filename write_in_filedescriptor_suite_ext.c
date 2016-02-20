/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_filedescriptor_suite_ext.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 10:21:57 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/20 10:22:02 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	**add_full_name(char **argv, char *name)
{
	char	**new;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (argv[size])
		size++;
	if (!(new = malloc(sizeof(char*) * MAX_ARGV_SIZE)))
		return (NULL);
	new = ft_set_null(new);
	new[0] = name;
	size = 1;
	while (argv[i])
	{
		new[size] = ft_strdup(argv[i]);
		i++;
		size++;
	}
	free_argv(argv);
	return (new);
}

void	print_file_missing_error(void)
{
	ft_putstr_fd("21sh: parse error near ", 2);
	write(2, "`\\", 2);
	write(2, "n'", 2);
	ft_putstr_fd("\n", 2);
}

int		check_cmd_n_file(char *cmd_to_exe, char *file, int res)
{
	if ((res = check_cmd(get_only_name(cmd_to_exe))) < 0)
	{
		ft_putstr_fd("\n", 2);
		return (0);
	}
	else if (!file)
	{
		print_file_missing_error();
		return (0);
	}
	return (res);
}

char	**get_args_after(char **args, char **args_after, int i, int args_i)
{
	while (args_after[i])
	{
		args[args_i] = ft_strdup(args_after[i]);
		i++;
		args_i++;
	}
	args[args_i] = NULL;
	return (args);
}
