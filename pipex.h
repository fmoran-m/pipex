#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
typedef struct s_files
{
	int	fd_infile;
	int	fd_outfile;
} t_file;
void	free_files(t_file *files, char *error);
void	*free_command(char *command);
void	*free_path(char *command, char **path);
#endif
