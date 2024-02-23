#include "pipex.h"

static char	*get_command(char *argv)
{
	char	*command;
	
	command = ft_strjoin("/", argv);
	if (!command)
		return(NULL);
	return (command);
}

char *get_path(char *argv, char **env) //Controlar el liberaciones y perror cuando no hay access
{
	int		i;
	char	**path;
	char	*temp;
	char	*search;
	char	*command;

	i = 0;
	if (access(argv, X_OK) == 0)
		return (argv);
	command = get_command(argv);
	if (!command)
		return(NULL);
	while (env[i] && (ft_strncmp(env[i], "PATH=", 5))) //Controlar también con la ruta absoluta
		i++;
	if (!env[i])
		return(free_command(command));
	temp = env[i] + 5;
	path = ft_split(temp, ':'); //Free
	if (!path)
		return(free_command(command));
	i = 0;
	while (1)
	{
		if (!path[i])
			break;
		search = ft_strjoin(path[i], command);
		if (!search)
			return (free_path(command, path));
		if (access(search, X_OK) == 0)
			break;
		i++;
	}
	if (!path[i])
	{
		perror("Command does not exist");
		exit(-1);
	}
	return (search);
}