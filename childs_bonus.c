/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:32 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/02/27 21:50:12 by fmoran-m         ###   ########.fr       */
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

int	open_here_doc(char *limiter, int *pipex)
{
	int	fd;
	char *buffer;

	buffer = NULL;
	fd = open(".here_doc.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		close(pipex[0]);
		close(pipex[1]);
		perror(OPEN_ERR);
		exit(1);
	}
	while(1)
	{
		ft_printf("> ");
		buffer = get_next_line(0);
		write(fd, buffer, ft_strlen(buffer));
		if (!ft_strncmp(buffer, limiter, ft_strlen(limiter)))
			break;
	}
	exit (0);
	return(fd);
}

void	exec_first_process(int *pipex, char **argv, char **env, int here_doc)
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
		if (here_doc == 1)
			fd_infile = open_here_doc(argv[2], pipex);
		else
			fd_infile = open_infile(argv[1], pipex);
		path = get_path(argv[2 + here_doc], env, pipex, fd_infile);
		close(pipex[0]);
		if (dup2(fd_infile, 0) == -1)
			free_exit(pipex, path, fd_infile, NULL);
		close(fd_infile);
		if (dup2(pipex[1], 1) == -1)
			free_exit(pipex, path, fd_infile, NULL);
		close(pipex[0]);
		exec_cmd(path, argv[2 + here_doc], env);
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
	{
		perror(NULL);
		exit(1);
	}
	if (pid == 0)
	{
		fd_outfile = open_outfile(argv[4], pipex);
		path = get_path(argv[3], env, pipex, fd_outfile);
		if (dup2(pipex[0], 0) == -1)
			free_exit(pipex, path, fd_outfile, NULL);
		close(pipex[0]);
		if (dup2(fd_outfile, 1) == -1)
			free_exit(pipex, path, fd_outfile, NULL);
		close(fd_outfile);
		exec_cmd(path, argv[3], env);
	}
}
