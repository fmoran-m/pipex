#include "pipex.h"

int	open_infile(char *infile, int *pipex)
{
	int	fd;

	if (access(infile, F_OK) != 0)
		free_exit(pipex, NULL, 0, ACC_ERR);
	fd = open(infile, O_RDWR);
	if (fd == -1)
		free_exit(pipex, NULL, 0, OPEN_ERR);
	return (fd);
}

int	open_outfile(char *outfile, int *pipex)
{
	int	fd;

	fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		free_exit(pipex, NULL, 0, OPEN_ERR);
	return (fd);
}