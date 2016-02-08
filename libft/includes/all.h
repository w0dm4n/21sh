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
# define READ_BUFFER 4096
# define PATH_MAX_SIZE 16192
# define COLOR_WHITE "\e[1;37m"
# define MAX_EXE_NAME 2048
# define MAX_ARGV_SIZE 8192
# define MAX_VAR_ENV_SIZE 4096

void		read_entry(int first);
void		handle_cmd(char *buffer);
int			check_cmd(char *cmd);
void		do_cmd(char *cmd, char *cmd_args, int res);
void		chdir_command(char *args);
char		*get_env(char *tofind);
void		print_all_env(void);
void		set_env(char *env, char *value_to_set);
char		**g_env;
void		print_error(char *name, int error_id);
int			get_path(char *path, char *args);
char		*get_subdir(char *path);
int			check_access_folder(char *real_path, char *args);
int			check_execve(char *file_name, char *all_path);
void		execute_binary(char *name, char *cmd_args, char **env, int res);
void		free_argv(char **argv);
void		change_or_add_env(char *args);
int			get_args_nbr(char *args);
void		un_set_env(char *args);
void		chdir_command_ext(char *args, char *path, int args_nbr);
void		change_folder(char *path, int change_path);
char		**set_argv(char **argv, char *name);
char		*get_name(char *name);
void		execute_binary_from_current_folder(char *exe, char *args);
int			check_stat(char *full_path, int print);
void		launch_process(char *path, char *name, char *cmd, char **env);
int			g_current_process;
void		sig_handler(int signo);
#endif
