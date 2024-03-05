/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:32 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/02/28 22:14:28 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	exec_first_process(int *pipex, char **argv, char **env)
{
	pid_t	pid;
	char	*path;
	int		fd_infile;

	fd_infile = 0;
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		exit(1);
	}
	if (pid == 0)
	{
		fd_infile = open_infile(argv[1], pipex);
		close(pipex[0]);
		if (dup2(fd_infile, STDIN_FILENO) == -1)
			free_exit(pipex, NULL, fd_infile, NULL);
		close(fd_infile);
		if (dup2(pipex[1], STDOUT_FILENO) == -1)
			free_exit(pipex, NULL, 0, NULL);
		close(pipex[1]);
		path = get_path(argv[2], env, NULL);
		exec_cmd(path, argv[2], env);
	}
}

void	exec_last_process(int *pipex, char **argv, char **env)
{
	pid_t	pid;
	char	*path;
	int		fd_outfile;

	close(pipex[1]);
	fd_outfile = 0;
	pid = fork();
	if (pid == -1)
		free_exit(pipex, NULL, 0, NULL);
	if (pid == 0)
	{
		fd_outfile = open_outfile(argv[4], pipex);
		if (dup2(pipex[0], STDIN_FILENO) == -1)
			free_exit(pipex, NULL, fd_outfile, NULL);
		close(pipex[0]);
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			free_exit(NULL, NULL, fd_outfile, NULL);
		close(fd_outfile);
		path = get_path(argv[3], env, NULL);
		exec_cmd(path, argv[3], env);
	}
}
