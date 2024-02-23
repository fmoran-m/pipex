#include "pipex.h"

int	open_infile(char *infile, t_global *global)
{
	int	fd;

	if (access(infile, F_OK) != 0)
	{
		free(global);
		perror("Access error");
		exit(-1);
	}
	fd = open(infile, O_RDWR);
	if (fd == -1)
	{
		free(global);
		perror("Open error");
		exit(-1);
	}
	return (fd);
}

int open_outfile(char *outfile, t_global *global)
{
	int	fd;

	fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		close(global->fd_outfile);
		free(global);
		perror("Open error");
		exit(-1);
	}
	return (fd);
}

void	argc_control(int argc)
{
	if (argc != 5)
	{
		ft_putendl_fd("Incorrect number of arguments", 2);
		exit (-1);
	}
}