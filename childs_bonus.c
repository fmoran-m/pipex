/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:32 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/03/01 20:49:17 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(char *path, char *argv, char **env)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		free_exit(NULL, path, 0, NULL);
	if (execve(path, cmd, env) == -1)
	{
		perror(NULL);
		free_matrix(cmd);
		free(path);
		exit(1);
	}
}

static void	in_child(t_global global, char **argv, char **env)
{
	int		fd_infile;
	char	*path;

	if (global.here_doc == 1)
	{
		open_here_doc(argv[2], global.pipex);
		fd_infile = open_infile(HDOC_FILE, global.pipex);
	}
	else
		fd_infile = open_infile(argv[1], global.pipex);
	close(global.pipex[0]);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		free_exit(global.pipex, NULL, fd_infile, NULL);
	close(fd_infile);
	if (global.here_doc)
		unlink(HDOC_FILE);
	if (dup2(global.pipex[1], STDOUT_FILENO) == -1)
		free_exit(global.pipex, NULL, 0, NULL);
	close(global.pipex[1]);
	path = get_path(argv[2 + global.here_doc], env, NULL);
	exec_cmd(path, argv[2 + global.here_doc], env);
}

void	exec_first_process(t_global global, char **argv, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		exit(1);
	}
	if (pid == 0)
		in_child(global, argv, env);
}

void	exec_last_process(t_global global, char **argv, char **env, int argc)
{
	pid_t	pid;
	char	*path;
	int		fd_outfile;

	close(global.pipex[1]);
	fd_outfile = 0;
	pid = fork();
	if (pid == -1)
		free_exit(global.pipex, NULL, 0, NULL);
	if (pid == 0)
	{
		fd_outfile = open_outfile(argv[argc - 1], global.pipex, global.here_doc);
		if (dup2(global.pipex[0], STDIN_FILENO) == -1)
			free_exit(global.pipex, NULL, fd_outfile, NULL);
		close(global.pipex[0]);
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			free_exit(global.pipex, NULL, fd_outfile, NULL);
		close(fd_outfile);
		path = get_path(argv[argc - 2], env, NULL);
		exec_cmd(path, argv[argc - 2], env);
	}
}
