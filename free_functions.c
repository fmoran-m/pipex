#include "pipex.h"

void	free_files(t_file *files, char *error)
{
	free(files);
	perror(error);
	exit(-1);
}

void	*free_command(char *command)
{
	free(command);
	return(NULL);
}

void	*free_path(char *command, char **path)
{
	int	i;

	i = 0;
	while(path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	free(command);
	return(NULL);
}