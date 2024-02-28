/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:38 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/02/28 17:56:47 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	argc_control(int argc, int here_doc)
{
	if (here_doc != 0 && argc < 6)
	{
		exit (1);
		ft_putendl_fd(ARGC_ERR, 2);
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
	if (!ft_strncmp(argv[1], "here__doc", 9))
		flag = 1;
	return (flag);
}

int	main(int argc, char **argv, char **env)
{
	int	pipex[2];
	int	status;
	int	here_doc;

	here_doc = check_here_doc(argv);
	argc_control(argc, here_doc);
	if (pipe(pipex) == -1)
	{
		perror(NULL);
		return (1);
	}
	exec_first_process(pipex, argv, env, here_doc);
	wait(&status);
	exec_last_process(pipex, argv, env);
	wait(&status);
	if (status != 0)
		return (1);
	return (0);
}
