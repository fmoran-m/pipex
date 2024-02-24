#include "pipex.h"

static t_global	*global_init(char **argv, char **env)
{
	t_global	*global;

	global = ft_calloc(1, sizeof(t_global));
	if (!global)
	{
		ft_putendl_fd("Memory allocation error", 2);
		exit(-1);
	}
	global->path1 = NULL;
	global->path2 = NULL;
	global->fd_infile = open_infile(argv[1], global);
	global->fd_outfile = open_outfile(argv[4], global);
	global->path1 = get_path(argv[2], env, global);
	global->path2 = get_path(argv[3], env, global);
	return (global);
}

int main(int argc, char **argv, char **env)
{
	pid_t		pid;
	int			fd[2];
	t_global	*global;

	argc_control(argc);
	global = global_init(argv, env);
	if(dup2(global->fd_infile, 0) == -1)
		free_exit_global(global);
	if(pipe(fd) == -1)
		free_exit_global(global);
	pid = fork();
	if (pid == -1)
		close_exit(fd, global);
	if (pid == 0)
		create_wrchild(fd, argv[2], global, env);
	else
	{
		close(fd[1]);
		pid = fork();
		if (pid == -1)
			close_fdzero_exit(fd, global);
		if (pid == 0)
		create_rdchild(fd, argv[3], global, env);
	}
	return (0);
}
