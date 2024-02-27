#include "pipex.h"

static char	*get_command(char *argv, int file_fd, int *pipex)
{
	char	*command;
	char	**temp;
	
	temp = ft_split(argv, ' ');
	if (!temp)
		free_exit(pipex, NULL, file_fd, NULL);
	command = ft_strjoin("/", temp[0]);
	if (!command)
	{
		free_matrix(temp);
		free_exit(pipex, NULL, file_fd, NULL);
	}
	free_matrix(temp);
	return (command);
}

static char *get_path_env(char **env, char *command, int file_fd, int *pipex)
{
	int		i;
	char	*mod_env;

	i = 0;
	while (env[i] && (ft_strncmp(env[i], "PATH=", 5))) //Controlar también con la ruta absoluta
		i++;
	if (!env[i])
	{
		free(command);
		free_exit(pipex, NULL, file_fd, "Path not founded");
	}
	mod_env = env[i] + 5;
	return(mod_env);
}

static char	*get_def_path(char **path, char *command, int file_fd, int *pipex)
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
		{
			free_matrix(path);
			free(command);
			free_exit(pipex, NULL, file_fd, NULL);
		}
		if (access(search, X_OK) == 0)
			found = 1;
		else
		{
			i++;
			free(search);
		}
	}
	if (!found)
	{
		free_matrix(path);
		free(command);
		free_exit(pipex, NULL, file_fd, "Command does not exist");
	}
	return (search);
}

char *get_path(char *argv, char **env, int file_fd, int *pipex)
{
	char	**path;
	char	*temp;
	char	*search;
	char	*command;

	if(!*argv)
		free_exit_err(pipex, NULL, file_fd, CMD_ERR);
	if (access(argv, X_OK) == 0)
		return (argv);
	command = get_command(argv, file_fd, pipex);
	temp = get_path_env(env, command, file_fd, pipex);
	path = ft_split(temp, ':'); //Free
	if (!path)
	{
		free(command);
		free(temp);
		free_exit(pipex, NULL, file_fd, NULL);
	}
	search = get_def_path(path, command, file_fd, pipex);
	free(command);
	free_matrix(path);
	return (search);
}