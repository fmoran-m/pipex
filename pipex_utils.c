#include "pipex.h"

t_file	*open_files(char *infile, char *outfile)
{
	t_file	*files;

	if (access(infile, F_OK) != 0)
	{
		perror("Access error");
		exit(-1);
	}
	files = ft_calloc(1, sizeof(t_file));
	if (!files)
	{
		ft_putendl_fd("Memory allocation error", 2);
		exit(-1);
	}
	files->fd_infile = open(infile, O_RDWR);
	if (files->fd_infile == -1)
		free_files(files, "Open error");
	files->fd_outfile = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (files->fd_outfile == -1)
		free_files(files, "Open error");
	return(files);
}

void	argc_control(int argc)
{
	if (argc != 5)
	{
		ft_putendl_fd("Incorrect number of arguments", 2);
		exit (-1);
	}
}