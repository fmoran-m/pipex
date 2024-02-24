#include "pipex.h"

void	free_exit_global(t_global *global)
{
	close(global->fd_infile);
	close(global->fd_outfile);
	if (global->path1)
		free(global->path1);
	if (global->path2)
		free(global->path1);
	free(global);
	exit(-1);
}

void	command_exit(char *command, t_global *global)
{
	perror("Path not founded");
	free(command);
	free_exit_global(global);
}

void	path_exit(char **path, char *command, t_global *global, char *error)
{
	int	i;

	i = 0;
	perror(error);
	free(command);
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	free_exit_global(global);
}

void	close_exit(int *fd, t_global *global)	
{
	close(fd[0]);
	close(fd[1]);
	free_exit_global(global);
}

void	close_fdzero_exit(int *fd, t_global *global)
{
	close(fd[0]);
	free_exit_global(global);
}