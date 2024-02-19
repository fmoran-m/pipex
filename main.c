#include "pipex.h"

char *get_path(char *argv, char **env)
{
	int		i;
	char	**path;
	char	*search;
	char	*command;

	command = ft_strjoin("/", argv);
	while (env[i] && (ft_strncmp(env[i], "PATH=", 5)))
		i++;
	env[i] = env[i] + 5;
	path = ft_split(env[i], ':'); //Free
	i = 0;
	search = ft_strjoin(path[i], command);
	while (path[i] && access(search, F_OK) != 0)
	{
		i++;
		free(search);
		search = ft_strjoin(path[i], command);
	}
	return (search);
}

int main(int argc, char **argv, char **env)
{
	char	*cmd1;
	char	*cmd2;
	pid_t	pid;
	int		fd[2];

	cmd1 = get_path(argv[2], env);
	cmd2 = get_path(argv[3], env);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execve(cmd1, NULL, env);
	}
	return 0;
}
