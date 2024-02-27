#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define CMD_ERR "Command does not exist: No such file or directory"
void	argc_control(int argc);
void	exec_first_process(int *pipex, char **argv, char **env);
void	exec_first_process(int *pipex, char **argv, char **env);
void	exec_last_process(int *pipex, char **argv, char **env);
int		open_infile(char *infile, int *pipex, char *path);
int		open_outfile(char *outfile, int *pipex, char *path);
void	exec_cmd(char *path, char *argv, char **env);
void	free_exit(int *pipex, char *path, int file_fd, char *error);
void	free_exit_err(int *pipex, char *path, int file_fd, char *error);
void	free_matrix(char **matrix);
char 	*get_path(char *argv, char **env, int *pipex);
void	exit_path(char **path, char *command, int *pipex);
void	exit_path_err(char **path, char *command, int *pipex);
void	free_exit_err(int *pipex, char *path, int file_fd, char *error);
#endif
