/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_entry_suite.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:29:23 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/22 14:29:25 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		clear_all_n_realloc(void)
{
	g_new_cmd = FALSE;
	free(g_cmd);
	if (!(g_cmd = (char*)malloc(sizeof(char) * READ_BUFFER)))
		return ;
	ft_bzero(g_cmd, READ_BUFFER);
	g_cursor_pos = 0;
	g_selected_position = set_arr_zero(g_selected_position, READ_BUFFER);
	dup2(g_fd, g_closed);
}
