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

int	open_infile(char *infile, int *pipex)
{
	int	fd;

	if (access(infile, F_OK) != 0)
		free_exit(pipex, NULL, 0, ACC_ERR);
	fd = open(infile, O_RDWR);
	if (fd == -1)
		free_exit(pipex, NULL, 0, OPEN_ERR);
	return (fd);
}

int	open_outfile(char *outfile, int *pipex, int here_doc)
{
	int	fd;

	if (here_doc == 1)
	{
		fd = open(outfile, O_RDWR | O_APPEND, O_CREAT, 0777);
		if (fd == -1)
			free_exit(pipex, NULL, 0, OPEN_ERR);
	}
	else
	{
		fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0777);
		if (fd == -1)
			free_exit(pipex, NULL, 0, OPEN_ERR);
	}
	return (fd);
}

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

void	open_here_doc(char *limiter, int *pipex)
{
	int	fd;
	char *buffer;
	int	limiter_len;
	int	buffer_len;

	buffer = NULL;
	buffer_len = 0;
	limiter_len = ft_strlen(limiter);
	fd = open(".here_doc.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		close(pipex[0]);
		close(pipex[1]);
		perror(OPEN_ERR);
		exit(1);
	}
	while(ft_strncmp(buffer, limiter, limiter_len) || limiter_len + 1 != buffer_len)
	{
		if (buffer)
			free(buffer);
		ft_printf("> ");
		buffer = get_next_line(0);
		buffer_len = ft_strlen(buffer);
		if ((ft_strncmp(buffer, limiter, limiter_len) || limiter_len + 1 != buffer_len))
			write(fd, buffer, buffer_len);
	}
	free(buffer);
	close(fd);
}

void	exec_first_process(t_global global, char **argv, char **env)
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
		if (global.here_doc == 1)
		{
			open_here_doc(argv[2], global.pipex);
			fd_infile = open_infile(".here_doc.txt", global.pipex);
		}
		else
			fd_infile = open_infile(argv[1], global.pipex);
		close(global.pipex[0]);
		if (dup2(fd_infile, 0) == -1)
			free_exit(global.pipex, NULL, fd_infile, NULL);
		close(fd_infile);
		if (global.here_doc)
			unlink(".here_doc.txt");
		if (dup2(global.pipex[1], 1) == -1)
			free_exit(global.pipex, NULL, 0, NULL);
		close(global.pipex[1]);
		path = get_path(argv[2 + global.here_doc], env, NULL);
		exec_cmd(path, argv[2 + global.here_doc], env);
	}
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
		if (dup2(global.pipex[0], 0) == -1)
			free_exit(global.pipex, NULL, fd_outfile, NULL);
		close(global.pipex[0]);
		if (dup2(fd_outfile, 1) == -1)
			free_exit(global.pipex, NULL, fd_outfile, NULL);
		close(fd_outfile);
		path = get_path(argv[argc - 2], env, NULL);
		exec_cmd(path, argv[argc - 2], env);
	}
}
