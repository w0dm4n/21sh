/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:32:15 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/26 04:33:43 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*get_name(char *name)
{
	char	*new;
	int		size;

	size = (ft_strlen(name) + 3);
	if (!(new = malloc(sizeof(char) * size)))
		return (NULL);
	new = ft_strcat(new, "./");
	new = ft_strcat(new, name);
	free(name);
	return (new);
}

char		**add_file_name(char **argv, char *name)
{
	char	**new;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (argv[size])
		size++;
	if (!(new = malloc(sizeof(char*) * MAX_ARGV_SIZE)))
		return (NULL);
	new = ft_set_null(new);
	new[0] = get_name(name);
	size = 1;
	while (argv[i])
	{
		new[size] = ft_strdup(argv[i]);
		i++;
		size++;
	}
	free_argv(argv);
	return (new);
}

void		launch_process_ext(char *get_path, char **argv, char **env)
{
	int		child_status;
	pid_t	child_pid;
	pid_t	tpid;

	child_pid = fork();
	if (child_pid == 0)
	{
		execve(get_path, argv, env);
		exit(0);
	}
	else
	{
		g_current_process = 1;
		signal(SIGINT, sig_handler);
		tpid = wait(&child_status);
		g_current_process = 0;
	}
}

void		launch_process(char *path, char *name, char *cmd, char **env)
{
	char	*get_path;
	int		size;
	char	**argv;

	argv = NULL;
	size = READ_BUFFER;
	if (!(get_path = malloc(sizeof(char) * size)))
		return ;
	get_path = ft_strcat(get_path, path);
	get_path = ft_strcat(get_path, "/");
	get_path = ft_strcat(get_path, name);
	if (cmd && cmd[0] && ft_strlen(cmd))
	{
		cmd = ft_strtrim(cmd);
		argv = ft_strsplit(cmd, ' ');
		argv = add_file_name(argv, name);
	}
	else
		argv = set_argv(argv, name);
	launch_process_ext(get_path, argv, env);
}

void		execute_binary(char *name, char *cmd_args, char **env, int res)
{
	char	**all_path;
	int		i;

	i = 0;
	all_path = ft_strsplit(get_env("PATH"), ':');
	while (all_path[i])
	{
		if (i == res)
			launch_process(all_path[i], name, cmd_args, env);
		i++;
	}
}
