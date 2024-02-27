#include "pipex.h"

void	free_exit(int *pipex, char *path, int file_fd, char *error)
{
	perror(error);
	if (pipex && pipex[0] != -1)
		close(pipex[0]);
	if (pipex && pipex[1] != -1)
		close(pipex[1]);
	if (path)
		free(path);
	if (file_fd && file_fd != -1)
		close(file_fd);
	exit(1);
}

void	free_exit_err(int *pipex, char *path, int file_fd, char *error)
{
	ft_putendl_fd(error, 2);
	if (pipex && pipex[0] != -1)
		close(pipex[0]);
	if (pipex && pipex[1] != -1)
		close(pipex[1]);
	if (path)
		free(path);
	if (file_fd && file_fd != -1)
		close(file_fd);
	exit(1);
}

void	free_matrix(char **matrix)
{
	int i;

	i = 0;
	while(matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}