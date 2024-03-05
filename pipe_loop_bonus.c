#include "pipex_bonus.h"

static void	loop_child(t_global global, t_temp temp, char **argv, char **env)
{
	close(temp.new[0]);
	if (dup2(global.pipex[0], STDIN_FILENO) == -1)
	{
		close(temp.new[1]);
		free_exit(global.pipex, NULL, 0, NULL);
	}
	close(global.pipex[1]);
	if (dup2(temp.new[1], STDOUT_FILENO) == -1)
	{
		close(temp.new[1]);
		free_exit(global.pipex, NULL, 0, NULL);
	}
	close(temp.new[1]);
	close(global.pipex[0]);
	temp.path = get_path(argv[temp.i], env, NULL);
	exec_cmd(temp.path, argv[temp.i], env);
}

t_global	pipe_loop(t_global global, char **argv, char **env, int argc)
{
	t_temp	temp;

	temp.i = 3;
	argc = argc - global.here_doc;
	while(temp.i < argc - 2)
	{
		if (pipe(temp.new) == -1)
			free_exit(global.pipex, NULL, 0, NULL);
		close(global.pipex[1]);
		temp.pid = fork();
		if (temp.pid == -1)
		{
			close(temp.new[0]);
			close(temp.new[1]);
			free_exit(global.pipex, NULL, 0, NULL);
		}
		if (temp.pid == 0)
			loop_child(global, temp, argv, env);
		wait(&temp.status);
		global.pipex[0] = temp.new[0];
		global.pipex[1] = temp.new[1];
		temp.i++;
	}
	return (global);
}
