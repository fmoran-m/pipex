/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:42 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/02/27 17:06:34 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define PATH		"PATH="
# define ARGC_ERR	"Incorrect number of arguments"
# define PATH_ERR	"Path not founded"
# define ACC_ERR	"Access error"
# define OPEN_ERR	"Open error"
# define CMD_ERR	"Command does not exist"
# define MEM_ERR	"Memory allocation error"

void	argc_control(int argc);
void	exec_first_process(int *pipex, char **argv, char **env);
void	exec_first_process(int *pipex, char **argv, char **env);
void	exec_last_process(int *pipex, char **argv, char **env);
int		open_infile(char *infile, int *pipex);
int		open_outfile(char *outfile, int *pipex);
void	exec_cmd(char *path, char *argv, char **env);
void	free_exit(int *pipex, char *path, int file_fd, char *error);
void	free_exit_err(int *pipex, char *path, int file_fd, char *error);
void	free_matrix(char **matrix);
char	*get_path(char *argv, char **env, int *pipex);
void	exit_path(char **path, char *command, int *pipex);
void	exit_path_err(char **path, char *command, int *pipex);
void	free_exit_err(int *pipex, char *path, int file_fd, char *error);
#endif
