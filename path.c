#include "pipex.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
		while(path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

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

static char *get_path_env(char **env, char *command, t_global *global)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i] && (ft_strncmp(env[i], "PATH=", 5))) //Controlar también con la ruta absoluta
		i++;
	if (!env[i])
		command_exit(command, global);
	temp = env[i] + 5;
	return(temp);
}

static char	*get_def_path(char **path, char *command, t_global *global)
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
			path_exit(path, command, global, "Memory allocation error");
		if (access(search, X_OK) == 0)
			found = 1;
		else
		{
			i++;
			free(search);
		}
	}
	if (!found)
		path_exit(path, command, global, "Command does not exist");
	free(command);
	free_path(path);
	return (search);
}

char *get_path(char *argv, char **env, t_global *global) //Controlar el liberaciones y perror cuando no hay access
{
	char	**path;
	char	*temp;
	char	*search;
	char	*command;

	if(!*argv)
	{
		ft_putendl_fd("Command does not exist: No such file or directory", 2);
		free_exit_global(global);
	}
	if (access(argv, X_OK) == 0)
		return (argv);
	command = get_command(argv, global);
	temp = get_path_env(env, command, global);
	path = ft_split(temp, ':'); //Free
	if (!path)
		command_exit(command, global);
	search = get_def_path(path, command, global);
	return (search);
}