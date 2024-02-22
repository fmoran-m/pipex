#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		fd[2];
	t_file	*files;

	argc_control(argc);
	files = open_files(argv[1], argv[4]);
	if(dup2(files->fd_infile, 0) == -1)
		free_files(files, "Dup error");
	if(pipe(fd) == -1)
		free_files(files, "Pipe error");
	pid = fork();
	if (pid == -1)
		free_files(files, "Pid error");
	if (pid == 0)
		create_wrchild(fd, argv[2], files, env);
	else
	{
		close(fd[1]);
		pid = fork();
		if (pid == -1)
			free_files(files, "Pid error");
		if (pid == 0)
		create_rdchild(fd, argv[3], files, env);
	}
	return 0;
}
