#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
typedef struct s_global
{
	int		fd_infile;
	int		fd_outfile;
	char	*path1;
	char	*path2;
} t_global;
void	*free_command(char *command);
void	free_exit_global(t_global *global);
void	*free_path(char *command, char **path);
void	argc_control(int argc);
char	*get_path(char *argv, char **env, t_global *global);
void	create_wrchild(int *fd, char *argv, t_global *global, char **env);
void	create_rdchild(int *fd, char *argv, t_global *global, char **env);
int		open_infile(char *infile, t_global *global);
int		open_outfile(char *outfile, t_global *global);
#endif
