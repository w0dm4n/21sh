/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_filedescriptor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 04:49:07 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/18 04:49:08 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	write_in_filedescriptor(char *cmd, int nbr, char to_find)
{
	char	*cmd_to_exec;
	char	*file_to_write_in;

	cmd_to_exec = get_separated_by_char(cmd, to_find, 0, nbr);
	file_to_write_in = get_separated_by_char(cmd, to_find, 1, nbr);
	ft_putstr(cmd_to_exec);
	ft_putstr(" TO : ");
	ft_putstr(file_to_write_in);
	ft_putstr("\n");
	//TODO ARGUMENT AFTER CMD (STRSPLIT AND CHECK CASE && STRSPLIT FILE SEE IF CASE IF
	//CASE ADD IN SPLIT OF CMD IF LEN ARRAY)
	/*if (nbr == 1)
		cmd_to_exec = 
	else if (nbr == 2)
		ft_putstr("add in");*/
}