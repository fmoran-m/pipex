/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:38 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/04/09 19:04:05 by fmoran-m         ###   ########.fr       */
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

int	wait_loop(t_global global, int status)
{
	while(global.iterator > 0)
	{
		wait(&status);
		global.iterator--;
	}
	return (status);
}

int	main(int argc, char **argv, char **env)
{
	int			status;
	t_global	global;

	status = 0;
	global.here_doc = check_here_doc(argv);
	argc_control(argc, global.here_doc);
	if (pipe(global.pipex) == -1)
		free_exit(NULL, NULL, 0, NULL);
	exec_first_process(global, argv, env);
	global = pipe_loop(global, argv, env, argc);
	exec_last_process(global, argv, env, argc);
	close(global.pipex[0]);
	wait_loop(global, status);
	if (status != 0)
	{
		if (global.here_doc == 1)
			unlink(HDOC_FILE);
		return (127);
	}
	return (0);
}
