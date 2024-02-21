#include "pipex.h"

static char *get_path(char *argv, char **env) //Controlar el liberaciones y perror cuando no hay access
{
	int		i;
	char	**path;
	char	*temp;
	char	*search;
	char	*command;

	i = 0;
	if (ft_strrchr(argv, '/'))
		command = ft_strrchr(argv, '/');
	else
	{
		command = ft_strjoin("/", argv);
		if (!command)
			return(NULL);
	}
	while (env[i] && (ft_strncmp(env[i], "PATH=", 5))) //Controlar también con la ruta absoluta
		i++;
	if (!env[i])
		return(free_command(command));
	temp = env[i] + 5;
	path = ft_split(temp, ':'); //Free
	if (!path)
		return(free_command(command));
	i = 0;
	search = ft_strjoin(path[i], command);
	if (!search)
		return (free_path(command, path));
	while (path[i] && access(search, X_OK) != 0)
	{
		i++;
		free(search);
		search = ft_strjoin(path[i], command);
		if(!search)
			return(free_path(command, path));
	}
	return (search);
}

static t_file	*open_files(char *infile, char *outfile)
{
	t_file	*files;

	if (access(infile, F_OK) != 0)
	{
		perror("Access error");
		exit(-1);
	}
	files = ft_calloc(1, sizeof(t_file));
	if (!files)
	{
		ft_putendl_fd("Memory allocation error", 2);
		exit(-1);
	}
	files->fd_infile = open(infile, O_RDWR);
	if (files->fd_infile == -1)
	{
		perror("Open error");
		free(files);
		exit(-1);
	}
	files->fd_outfile = open(outfile, O_RDWR | O_CREAT, 0777);
	if (files->fd_infile == -1)
	{
		perror("Open error");
		free(files);
		exit(-1);
	}
	return(files);
}

static void	argc_control(int argc)
{
	if (argc != 5)
	{
		ft_putendl_fd("Incorrect number of arguments", 2);
		exit (-1);
	}
}

static void	create_wrchild(int *fd, char *argv, t_file *files, char **env)
{
	char	**final_cmd;
	char	*cmd;

	close(fd[0]);
	if(dup2(fd[1], 1) == -1)
		free_files(files, "Dup error");
	close(fd[1]);
	final_cmd = ft_split(argv, ' ');
	if (!final_cmd)
		free_files(files, "Allocation error");
	cmd = get_path(argv, env);
	if (!cmd)
		free_files(files, "Env error");
	execve(cmd, final_cmd, env);
}

static void create_rdchild(int *fd, char *argv, t_file *files, char **env)
{
	char	**cmd;
	char	*path;

	if (dup2(fd[0], 0) == -1)
		free_files(files, "Dup error");
	close(fd[0]);
	if (dup2(files->fd_outfile, 1) == -1)
		free_files(files, "Dup error");
	cmd = ft_split(argv, ' ');
	if (!cmd)
		free_files(files, "Allocation error");
	path = get_path(argv, env);
	if (!path)
		free_files(files, "Env error");
	execve(path, cmd, env);
}

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
