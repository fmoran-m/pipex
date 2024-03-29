/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:11:05 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/03/05 17:01:08 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	close_bf(int fd)
{
	close(fd);
	fd = -1;
	return (fd);
}

int	open_infile(char *infile, int *pipex)
{
	int	fd;

	if (access(infile, F_OK) != 0)
		free_exit(pipex, NULL, 0, ACC_ERR);
	fd = open(infile, O_RDONLY);
	if (fd == -1)
		free_exit(pipex, NULL, 0, OPEN_ERR);
	return (fd);
}

int	open_outfile(char *outfile, int *pipex, int here_doc)
{
	int	fd;

	if (here_doc == 1)
	{
		fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			free_exit(pipex, NULL, 0, OPEN_ERR);
	}
	else
	{
		fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			free_exit(pipex, NULL, 0, OPEN_ERR);
	}
	return (fd);
}

void	open_here_doc(char *limiter, int *pipex)
{
	int		fd;
	char	*buffer;
	int		limiter_len;
	int		buffer_len;

	buffer = NULL;
	buffer_len = 0;
	limiter_len = ft_strlen(limiter);
	fd = open(".here_doc.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		free_exit(pipex, NULL, 0, OPEN_ERR);
	while (ft_strncmp(buffer, limiter, limiter_len)
		|| limiter_len + 1 != buffer_len)
	{
		if (buffer)
			free(buffer);
		ft_printf("> ");
		buffer = get_next_line(0);
		buffer_len = ft_strlen(buffer);
		if ((ft_strncmp(buffer, limiter, limiter_len)
				|| limiter_len + 1 != buffer_len))
			write(fd, buffer, buffer_len);
	}
	free(buffer);
	close(fd);
}
