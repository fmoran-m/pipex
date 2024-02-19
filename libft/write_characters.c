/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:59:47 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/12/04 14:26:45 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	write_char(va_list args)
{
	int		c;
	ssize_t	bytes;

	c = va_arg(args, int);
	bytes = write(1, &c, 1);
	return (bytes);
}

int	write_string(va_list args)
{
	char	*str;
	int		i;
	char	*null;

	i = 0;
	null = "(null)";
	str = va_arg(args, char *);
	if (!str)
	{
		while (null[i])
		{
			if (write(1, &null[i], 1) == -1)
				return (-1);
			i++;
		}
		return (i);
	}
	while (str[i])
	{
		if (write(1, &str[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	write_module(void)
{
	ssize_t	bytes;

	bytes = write(1, "%", 1);
	return (bytes);
}
