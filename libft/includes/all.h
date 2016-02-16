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
# define CTRL_S 19
# define CTRL_E 5
# define COLOR_RED "\e[0;31m"
# define PRINT_SELECTED "\e[1;37m\e[46m"
# define RESET "\e[0;37m"
# define DEFAULT_COLOR "\e[1;37m"

void			read_user_entry(int read);
char			**alloc_cmd(char **current_cmd);
int				*set_arr_zero(int *array, int to_set);
void			grab_signal(void);
void			free_cmd_n_prompt(int signo);
int				move_cursor(int to_print);
void			delete_current_character(void);
void			move_cursor_one_line_up(void);
void			move_cursor_left(void);
void			move_cursor_one_line_down(void);
void			move_cursor_to(int pos);
void			set_saved_cursor(void);
void			save_cursor_pos(void);
void			delete_x_characters(int to_del);
void			move_cursor_right(void);
void			delete_current_line(void);
void			reset_cursor(void);
void			free_array(char **array);
void			refresh_stdout_del(char *g_cmd);
void			refresh_stdout(char *g_cmd);
void			refresh_stdout_selected(char *g_cmd);
void			print_logs(char *to_print);
void			move_cursor_on_the_last_word(char *g_cmd);
void			move_cursor_on_the_next_word(char *g_cmd);
char			*get_args(char *buffer, int i, int i_2);
char			*get_real_cmd(char *buffer, int i, int res, char *get_cmd);
char			**add_in_front(char **logs, char *cmd);
char			*add_in(char *g_cmd, int pos, char *toadd, int i);
char			*get_new_cmdncopy(char *g_cmd, int *selected_pos);
void			go_home(char *g_cmd);
int				count_char(char *string, char to_find);
char			*del_in(char *g_cmd, int pos);
char			**alloc_cmd(char **current_cmd);
int				check_special_chars(char *g_cmd);
void			print_color_n_prompt(void);
int				check_hook(char *g_cmd, int count_1, int count_2, int count_f);
int				check_accolade(char *g_cmd, int count_1, int count_2, int c);
void			enter_key(void);
void			print_or_add_in_stdout(int ascii_value, char *buff);
void			control_d(int size);
int				get_ascii_value(char *buff);
void			clear_screen_term(void);
void			control_e(void);
void			control_s(void);
void			arrow_down(void);
void			arrow_up(void);
void			arrow_right(void);
void			arrow_left(void);
void			backspace(void);
void			move_up(void);
void			move_down(void);
int				g_new_cmd;
char			*g_cmd;
int				g_cursor_pos;
int				g_current_cmd;
char			**g_logs;
int				g_logs_to_print;
struct winsize	g_size;
int				*g_selected_position;
#endif
