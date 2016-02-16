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
# include <term.h>
# include <stdio.h>
# include <sys/ioctl.h>
# define READ_BUFFER 4096
# define READ_CHAR 20
# define LOGS_BUFFER 10024
# define COLOR_WHITE "\e[1;37m"
# define MAX_EXE_NAME 2048
# define MAX_ARGV_SIZE 8192
# define MAX_VAR_ENV_SIZE 4096
# define COLOR_WHITE "\e[1;37m"
# define CLEAR_SCREEN "\033[2J"
# define TRUE 1
# define FALSE 0
# define NEW_CMD 10
# define ARROW_UP 183
# define ARROW_DOWN 184
# define ARROW_LEFT 186
# define ARROW_RIGHT 185
# define BACKSPACE 127
# define PRINT_CURSOR_POS "\033[6n"
# define HOME 190
# define END 188
# define CTRL_R 18
# define CTRL_G 7
# define CTRL_D 4
# define CTRL_L 12
# define CLEAR_SCREEN "\033[2J"
# define CTRL_U 21
# define CTRL_B 2
# define CTRL_S 19 // selectionner
# define CTRL_E 5 // coller
# define COLOR_RED "\e[0;31m"
# define PRINT_SELECTED "\e[1;37m\e[46m"
# define RESET "\e[0;37m"
# define DEFAULT_COLOR "\e[1;37m"

void			read_user_entry(int read);
char			**alloc_cmd(char **current_cmd);
int				*set_array_as_zero(int *array, int to_set);
int				g_new_cmd;
char			*g_cmd;
int				g_cursor_pos;
int				g_current_cmd;
char			**g_logs;
int				g_logs_to_print;
struct winsize	g_size;
int				*g_selected_position;
#endif
