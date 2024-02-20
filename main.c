#include "pipex.h"

static char *get_path(char *argv, char **env) //Controlar el liberaciones y perror cuando no hay access
{
	int		i;
	char	**path;
	char	*temp;
	char	*search;
	char	*command;

	i = 0;
	command = ft_strjoin("/", argv);
	while (env[i] && (ft_strncmp(env[i], "PATH=", 5)))
		i++;
	if (!env[i])
		exit(-1);
	temp = env[i] + 5;
	path = ft_split(temp, ':'); //Free
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

static void	check_files(char *infile, char *outfile)
{
	if (access(infile, F_OK) != 0
			|| access(outfile, F_OK) != 0)
	{
		perror("Access error");
		exit(-1);
	}
}

int main(int argc, char **argv, char **env)
{
	char	*cmd1;
	char	*cmd2;
	pid_t	pid;
	int		fd[2];
	int		fd_infile;
	int		fd_outfile;

	if (argc != 5)
	{
		ft_putendl_fd("Incorrect number of arguments", 2);
		return (-1);
	}
	check_files(argv[1], argv[4]);
	cmd1 = get_path(argv[2], env);
	cmd2 = get_path(argv[3], env);
	fd_infile = open(argv[1], O_RDWR);
	fd_outfile = open(argv[4], O_RDWR);
	if (fd_infile == -1)
		return (-1);
	dup2(fd_infile, 0);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		char **final_cmd1 = ft_split(argv[2], ' ');
		execve(cmd1, final_cmd1, env);
	}
	else
	{
		close(fd[1]);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			dup2(fd_outfile, 1);
			char **final_cmd2 = ft_split(argv[3], ' ');
			execve(cmd2, final_cmd2, env);
		}
	}
	return 0;
}
