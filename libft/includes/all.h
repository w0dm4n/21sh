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
# define MAX_LINE 1024
# define READ_CHAR 20
# define LOGS_BUFFER 10024
# define COLOR_WHITE "\e[1;37m"
# define MAX_EXE_NAME 2048
# define MAX_ARGV_SIZE 8192
# define MAX_VAR_ENV_SIZE 4096
# define PATH_MAX_SIZE 16192
# define FILE_BUFFER 161920
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
# define TABULATION 9

void			read_user_entry(int read);
char			**alloc_cmd(char **current_cmd);
int				*set_arr_zero(int *array, int to_set);
void			grab_signal_n_alloc(void);
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
char			*meurs_en_enfer(char *satan);
void			prompt_again_with_cmd(void);
void			handle_all_cmds(char *buffer);
void			handle_cmd(char *buffer);
int				check_cmd(char *cmd);
void			do_cmd(char *cmd, char *cmd_args, int res);
void			chdir_command(char *args);
char			*get_env(char *to_find);
void			set_env(char *env, char *value_to_set);
void			print_all_env(void);
void			chdir_command_ext(char *args, char *path, int args_nbr);
int				check_execve(char *file_name, char *all_path);
int				get_path(char *path, char *args);
int				get_args_nbr(char *args);
void			change_folder(char *path, int change_path);
char			*get_subdir(char *path);
int				check_access_folder(char *real_path, char *args);
void			change_or_add_env(char *args);
void			add_in_env(char *var, char *content);
void			un_set_env(char *args);
void			execute_binary_from_current_folder(char *exe, char *args);
void			execute_from_asked_dir(char *cmd, char **env, char *cmd_args);
void			execute_binary(char *name, char *cmd_args, char **env, int res);
int				check_stat(char *full_path, int print);
void			launch_process(char *path, char *name, char *cmd, char **env);
void			free_argv(char **argv);
char			**set_argv(char **argv, char *name);
void			launch_process_ext(char *get_path, char **argv, char **env);
char			*get_name(char *name);
void			handle_special_case(char *cmd);
char			*get_separated_by_char(char *cmd, char to_find, int pos, int nbr);
void			write_in_filedescriptor(char *cmd, int nbr, char to_find);
char			**add_file_name(char **argv, char *name);
char			**get_cmd_args(char **args_before, char **args_after);
char			*get_only_name(char *cmd_to_exec);
int				check_permissons_file(char *file_name);
char			*get_path_and_name(int res, char *cmd);
char			*get_delete_cmd(char *file_name);
void			print_file_missing_error(void);
int				check_cmd_n_file(char *cmd_to_exe, char *file, int res);
char			**get_args_after(char **args, char **args_after, int i, int args_i);
void			do_ls_f(void);
void			exec_with_filedescriptor(char *cmd, int nbr, char to_find);
char			**add_full_name(char **argv, char *name);
void			seek_and_print(char *buffer);
char			**get_all_files_from_current_directory(DIR *dir);
int				get_size(char *str);
char			**alloc_array(char **array, char **to_alloc);
char			**get_all_occur(char **array, char **all_occur, char *to_cmd, int size);
char			*get_occur_extension(char *occur);
char			*get_multi_line_cmd(char *g_cmd);
int				g_new_cmd;
char			*g_cmd;
int				g_cursor_pos;
int				g_current_cmd;
char			**g_logs;
int				g_logs_to_print;
struct winsize	g_size;
int				*g_selected_position;
char			**g_env;
int				g_current_process;
int				g_multi_line;
char			**g_multi_line_data;
#endif
