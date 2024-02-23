#include "pipex.h"

static char	*get_command(char *argv, t_global *global)
{
	char	*command;
	
	command = ft_strjoin("/", argv);
	if (!command)
	{
		ft_putendl_fd("Memory allocation error", 2);
		free_exit_global(global);
	}
	return (command);
}

char *get_path(char *argv, char **env, t_global *global) //Controlar el liberaciones y perror cuando no hay access
{
	int		i;
	char	**path;
	char	*temp;
	char	*search;
	char	*command;

	i = 0;
	if (access(argv, X_OK) == 0)
		return (argv);
	command = get_command(argv, global);
	while (env[i] && (ft_strncmp(env[i], "PATH=", 5))) //Controlar también con la ruta absoluta
		i++;
	if (!env[i])
	{
		perror("Path not founded");
		free(command);
		free_exit_global(global);
	}
	temp = env[i] + 5;
	path = ft_split(temp, ':'); //Free
	if (!path)
	{
		ft_putendl_fd("Memory allocation error", 2);
		free(command);
		free_exit_global(global);
	}
	i = 0;
	while (1)
	{
		if (!path[i])
			break;
		search = ft_strjoin(path[i], command);
		if (!search)
		{
			ft_putendl_fd("Memory allocation error", 2);
			free(command);
			i = 0;
			while(path[i])
			{
				free(path[i]);
				i++;
			}
			free(path);
			free_exit_global(global);
		}
		if (access(search, X_OK) == 0)
			break;
		i++;
	}
	if (!path[i])
	{
		perror("Command does not exist");
		free(command);
		i = 0;
		while(path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
		free_exit_global(global);
	}
	free(command);
	i = 0;
	while(path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return (search);
}