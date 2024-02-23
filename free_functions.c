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