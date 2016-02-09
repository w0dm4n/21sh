/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 21:01:27 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/24 21:03:25 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H
# include "libft.h"
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# define READ_BUFFER 4096
# define PATH_MAX_SIZE 16192
# define COLOR_WHITE "\e[1;37m"
# define MAX_EXE_NAME 2048
# define MAX_ARGV_SIZE 8192
# define MAX_VAR_ENV_SIZE 4096
# define COLOR_WHITE "\e[1;37m"

void		read_user_entry(void);
#endif
