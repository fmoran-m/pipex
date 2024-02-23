#include "pipex.h"

void	create_wrchild(int *fd, char *argv, t_file *files, char **env, char *path)
{
	char	**final_cmd;

	close(fd[0]);
	if(dup2(fd[1], 1) == -1)
		free_files(files, "Dup error");
	close(fd[1]);
	final_cmd = ft_split(argv, ' ');
	if (!final_cmd)
		free_files(files, "Allocation error");
	execve(path, final_cmd, env);
}

void	create_rdchild(int *fd, char *argv, t_file *files, char **env, char *path)
{
	char	**cmd;

	if (dup2(fd[0], 0) == -1)
		free_files(files, "Dup error");
	close(fd[0]);
	if (dup2(files->fd_outfile, 1) == -1)
		free_files(files, "Dup error");
	cmd = ft_split(argv, ' ');
	if (!cmd)
		free_files(files, "Allocation error");
	execve(path, cmd, env);
}