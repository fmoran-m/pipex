#include "pipex.h"

void	create_wrchild(int *fd, char *argv, t_global *global, char **env)
{
	char	**final_cmd;

	close(fd[0]);
	if(dup2(fd[1], 1) == -1)
	{
		perror("Dup error");
		close(fd[1]);
		free_exit_global(global);
	}
	close(fd[1]);
	final_cmd = ft_split(argv, ' ');
	if (!final_cmd)
	{
		ft_putendl_fd("Memory allocation error", 2);
		free_exit_global(global);
	}
	execve(global->path1, final_cmd, env);
}

void	create_rdchild(int *fd, char *argv, t_global *global, char **env)
{
	char	**cmd;

	if (dup2(fd[0], 0) == -1)
	{
		perror("Dup error");
		close(fd[0]);
		free_exit_global(global);
	}
	close(fd[0]);
	if (dup2(global->fd_outfile, 1) == -1)
	{
		perror("Dup error");
		free_exit_global(global);
	}
	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		ft_putendl_fd("Memory allocation error", 2);
		free_exit_global(global);
	}
	execve(global->path2, cmd, env);
}