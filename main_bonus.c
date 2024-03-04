/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:38 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/03/01 21:07:31 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	argc_control(int argc, int here_doc)
{
	if (here_doc != 0 && argc < 6)
	{
		ft_putendl_fd(ARGC_ERR, 2);
		exit (1);
	}
	else
	{
		if (argc < 5)
		{
			ft_putendl_fd(ARGC_ERR, 2);
			exit (1);
		}
	}
}

int	check_here_doc(char **argv)
{
	int	flag;

	flag = 0;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		flag = 1;
	return (flag);
}

t_global	pipe_loop(t_global global, char **argv, char **env, int argc)
{
	int		i;
	char	*path;
	pid_t	pid;
	int		status;
	int		new[2];

	i = 3;
	argc = argc - global.here_doc;
	while(i < argc - 2)
	{
		if (pipe(new) == -1)
			free_exit(global.pipex, NULL, 0, NULL);
		close(global.pipex[1]);
		pid = fork();
		if (pid == -1)
		{
			close(new[0]);
			close(new[1]);
			free_exit(global.pipex, NULL, 0, NULL);
		}
		if (pid == 0)
		{
			close(new[0]);
			if (dup2(global.pipex[0], 0) == -1)
			{
				close(new[1]);
				free_exit(global.pipex, NULL, 0, NULL);
			}
			close(global.pipex[1]);
			if (dup2(new[1], 1) == -1)
			{
				close(new[1]);
				free_exit(global.pipex, NULL, 0, NULL);
			}
			close(new[1]);
			close(global.pipex[0]); //OJO CON ESTO, PUEDE ROMPERMELO
			path = get_path(argv[i], env, NULL);
			exec_cmd(path, argv[i], env);
		}
		wait(&status);
		global.pipex[0] = new[0];
		global.pipex[1] = new[1];
		i++;
	}
	return (global);
}

int	main(int argc, char **argv, char **env)
{
	int			status;
	t_global	global;

	global.here_doc = check_here_doc(argv);
	argc_control(argc, global.here_doc);
	if (pipe(global.pipex) == -1)
	{
		perror(NULL);
		return (1);
	}
	exec_first_process(global, argv, env);
	wait(&status);
	global = pipe_loop(global, argv, env, argc);
	exec_last_process(global, argv, env, argc);
	wait(&status);
	if (status != 0)
		return (1);
	return (0);
}
