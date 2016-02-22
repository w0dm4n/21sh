/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 01:27:27 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/16 01:27:28 by frmarinh         ###   ########.fr       */
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
		g_selected_position = set_arr_zero(g_selected_position, READ_BUFFER);
	}
}

void	grab_signal_n_alloc(void)
{
	signal(SIGINT, free_cmd_n_prompt);
	if (!(g_selected_position = malloc(sizeof(int*) * READ_BUFFER)))
		return ;
	if (!(g_multi_line_data = malloc(sizeof(char) * MAX_LINE)))
		return ;
	if (!(g_term = malloc(sizeof(struct termios))))
		return ;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

int		count_char(char *string, char to_find)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (string[i])
	{
		if (string[i] == to_find)
			count++;
		i++;
	}
	return (count);
}

int		*set_arr_zero(int *array, int to_set)
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
