/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:35 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/03/05 16:10:04 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_exit(int *pipex, char *path, int file_fd, char *error)
{
	perror(error);
	if (pipex[0] != -1)
		close(pipex[0]);
	if (pipex[1] != -1)
		close(pipex[1]);
	if (path)
		free(path);
	if (file_fd)
		close(file_fd);
	exit(1);
}

void	exit_path(char **path, char *command, int *pipex)
{
	free_matrix(path);
	free(command);
	free_exit(pipex, NULL, 0, CMD_ERR);
}

void	exit_path_err(char **path, char *command, int *pipex)
{
	free_matrix(path);
	free(command);
	free_exit_err(pipex, NULL, 0, MEM_ERR);
}

void	free_exit_err(int *pipex, char *path, int file_fd, char *error)
{
	ft_putendl_fd(error, 2);
	if (pipex[0] != -1)
		close(pipex[0]);
	if (pipex[1] != -1)
		close(pipex[1]);
	if (path)
		free(path);
	if (file_fd)
		close(file_fd);
	exit(1);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
