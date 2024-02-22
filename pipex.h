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
void	create_rdchild(int *fd, char *argv, t_file *files, char **env);
void	create_wrchild(int *fd, char *argv, t_file *files, char **env);
void	argc_control(int argc);
char	*get_path(char *argv, char **env);
t_file	*open_files(char *infile, char *outfile);
#endif
