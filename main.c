/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:41:38 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/03/06 14:50:40 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	argc_control(int argc)
{
	if (argc != 5)
	{
		ft_putendl_fd(ARGC_ERR, 2);
		exit (1);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	pipex[2];
	int	status;

	argc_control(argc);
	if (pipe(pipex) == -1)
		free_exit(NULL, NULL, 0, NULL);
	exec_first_process(pipex, argv, env);
	wait(&status);
	exec_last_process(pipex, argv, env);
	wait(&status);
	close(pipex[0]);
	if (status != 0)
		return (1);
	return (0);
}
