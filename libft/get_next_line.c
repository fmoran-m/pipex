/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:38:48 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/12/05 15:06:24 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_intro(char *buf)
{
	int	i;

	if (!buf)
		return (0);
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*read_line(int fd, char *file)
{
	char	*buf;
	char	*temp;
	ssize_t	buf_read;

	if (!file)
		file = ft_strdup("");
	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (free_file(&file));
	buf_read = 1;
	while (buf_read > 0 && !is_intro(buf))
	{
		buf_read = read(fd, buf, BUFFER_SIZE);
		if (buf_read == -1)
			return (free(buf), free_file(&file));
		buf[buf_read] = 0;
		temp = ft_strjoin(file, buf);
		if (!temp)
			return (free (buf), free_file(&file));
		free (file);
		file = temp;
	}
	free (buf);
	return (file);
}

static char	*new_line(char *file)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (file[i] != '\n' && file[i])
		i++;
	if (!file[i])
		return (file);
	i++;
	line = (char *)ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = file[j];
		j++;
	}
	return (line);
}

static char	*new_file(char *file, char *line)
{
	char	*str;
	int		i;
	int		j;

	if (!is_intro(file))
		return (NULL);
	i = ft_strlen(file);
	j = ft_strlen(line);
	str = (char *)ft_calloc((i - j) + 2, sizeof(char));
	if (!str)
		return (free_file(&file));
	i = 0;
	while (file[j])
	{
		str[i] = file[j];
		i++;
		j++;
	}
	free_file(&file);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*file;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file = read_line(fd, file);
	if (!file)
		return (NULL);
	if (!*file)
		return (free_file(&file));
	line = new_line(file);
	if (!line)
		return (free_file(&file));
	file = new_file(file, line);
	return (line);
}
