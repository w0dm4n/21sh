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

int		main(int argc, char **argv, char **env)
{
	env = NULL;
	if (argc != 1 || argv[1])
		ft_putstr("21sh do not take any argument !\n");
	else
		read_user_entry();
	return (0);
}
