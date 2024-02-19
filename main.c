#include "pipex.h"

char *get_path(char *argv, char **env)
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

int main(int argc, char **argv, char **env)
{
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
	pid_t	pid;
	int		infile;
	int		outfile;
	int		fd[2];

	if (argc != 3)
	{
		ft_putendl_fd("Incorrect number of arguments", 2);
		return (-1);
	}
	cmd1 = ft_split(argv[1], ' ');
	cmd2 = ft_split(argv[2], ' ');
	path1 = get_path(cmd1[0], env);
	path2 = get_path(cmd2[0], env);
	infile = open("infile.txt", O_RDWR)
	outfile = open("outfile.txt", O_RDWR);
	dup2(infile , 0); //Cogemos la info del infile
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1); //Vamos a ejecutar el comando. Printeamos en el fd[1] en lugar de en la salida estándar
		close(fd[1]);
		execve(path1, cmd1, env);
	}
	else
	{
		close(fd[1]);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[0], 0); //Recogemos de la pipe
			close(fd[0]);
			dup2(outfile, 1); //Lo llevamos al archivo final
			execve(path2, cmd2, env);
		}
		else
			close(fd[0]);

	}
	return 0;
}
