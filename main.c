/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 09:43:46 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/08 09:44:24 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	free_cmd_n_prompt(int signo)
{
	if (signo == SIGINT)
	{
		ft_bzero(g_cmd, READ_BUFFER);
		g_current_cmd++;
		g_cursor_pos = 0;
		g_logs_to_print = 0;
		ft_putstr("\n");
		ft_putstr("$> ");
		g_selected_position = set_array_as_zero(g_selected_position, READ_BUFFER);
		// add case for logs to avoid malloc: *** error for object
	}
}

void	grab_signal(void)
{
	signal(SIGINT, free_cmd_n_prompt);
}

int		*set_array_as_zero(int *array, int to_set)
{
	int		i;

	i = 0;

	while (i <= to_set)
	{
		array[i] = 0;
		i++;
	}
	return (array);
}

int		main(int argc, char **argv, char **env)
{
	env = NULL;
	if (argc != 1 || argv[1])
		ft_putstr("21sh do not take any argument !\n");
	else
	{
		grab_signal();
		if (!(g_selected_position = malloc(sizeof(int*) * READ_BUFFER)))
			return (-1);
		g_selected_position = set_array_as_zero(g_selected_position, READ_BUFFER);
		g_cursor_pos = 0;
		g_current_cmd = 0;
		g_logs_to_print = 0;
		if (!(g_logs = alloc_cmd(g_logs)))
			return (-1);
		if (!(g_cmd = ft_strnew(READ_BUFFER)))
			return (-1);
		g_new_cmd = FALSE;
		read_user_entry(FALSE);
	}
	return (0);
}
