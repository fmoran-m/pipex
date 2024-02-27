/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:40 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/02/27 19:57:10 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_command(char *argv, int *pipex, int fd_file)
{
	char	*command;
	char	**temp;

	temp = ft_split(argv, ' ');
	if (!temp)
		free_exit(pipex, NULL, fd_file, NULL);
	command = ft_strjoin("/", temp[0]);
	if (!command)
	{
		free_matrix(temp);
		free_exit(pipex, NULL, fd_file, NULL);
	}
	free_matrix(temp);
	return (command);
}

static char	*get_path_env(char **env, char *command, int *pipex, int fd_file)
{
	int		i;
	char	*mod_env;

	i = 0;
	while (env[i] && (ft_strncmp(env[i], PATH, 5)))
		i++;
	if (!env[i])
	{
		free(command);
		free_exit(pipex, NULL, fd_file, PATH_ERR);
	}
	mod_env = env[i] + 5;
	return (mod_env);
}

static char	*get_def_path(char **path, char *command, int *pipex, int fd_file)
{
	int		i;
	int		found;
	char	*search;

	i = 0;
	found = 0;
	while (path[i] && !found)
	{
		search = ft_strjoin(path[i], command);
		if (!search)
			exit_path_err(path, command, pipex, fd_file);
		if (access(search, X_OK) == 0)
			found = 1;
		else
		{
			i++;
			free(search);
		}
	}
	if (!found)
		exit_path(path, command, pipex, fd_file);
	return (search);
}

char	*get_path(char *argv, char **env, int *pipex, int fd_file)
{
	char	**path;
	char	*temp;
	char	*search;
	char	*command;

	if (!*argv)
		free_exit_err(pipex, NULL, fd_file, CMD_ERR);
	if (access(argv, X_OK) == 0)
		return (argv);
	command = get_command(argv, pipex, fd_file);
	temp = get_path_env(env, command, pipex, fd_file);
	path = ft_split(temp, ':');
	if (!path)
	{
		free(command);
		free(temp);
		free_exit(pipex, NULL, fd_file, NULL);
	}
	search = get_def_path(path, command, pipex, fd_file);
	free(command);
	free_matrix(path);
	return (search);
}
