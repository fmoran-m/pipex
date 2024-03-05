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

int	main(int argc, char **argv, char **env)
{
	int			status;
	t_global	global;

	global.here_doc = check_here_doc(argv);
	argc_control(argc, global.here_doc);
	if (pipe(global.pipex) == -1)
		free_exit(NULL, NULL, 0, NULL);
	exec_first_process(global, argv, env);
	wait(&status);
	global = pipe_loop(global, argv, env, argc);
	exec_last_process(global, argv, env, argc);
	wait(&status);
	if (status != 0)
		return (1);
	return (0);
}
