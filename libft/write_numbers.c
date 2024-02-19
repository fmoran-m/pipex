/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:57:30 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/12/04 14:26:56 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	write_upper_hex(va_list args)
{
	ssize_t			temp;
	unsigned int	type;
	int				i;
	char			*num;

	i = 0;
	temp = 0;
	type = va_arg(args, unsigned int);
	num = ft_upper_hextoa(type);
	if (!num)
		return (-1);
	while (num[i])
	{
		temp = write(1, &num[i], 1);
		if (temp == -1)
			return (free(num), -1);
		i++;
	}
	free (num);
	return (i);
}

int	write_lower_hex(va_list args)
{
	ssize_t			temp;
	unsigned int	type;
	int				i;
	char			*num;

	i = 0;
	temp = 0;
	type = va_arg(args, unsigned int);
	num = ft_lower_hextoa(type);
	if (!num)
		return (-1);
	while (num[i])
	{
		temp = write(1, &num[i], 1);
		if (temp == -1)
			return (free(num), -1);
		i++;
	}
	free (num);
	return (i);
}

int	write_pointer_address(va_list args)
{
	ssize_t				temp;
	unsigned long long	type;
	int					i;
	char				*num;

	i = 0;
	temp = 0;
	temp = write (1, "0", 1);
	if (temp == -1)
		return (-1);
	temp = write (1, "x", 1);
	if (temp == -1)
		return (-1);
	type = va_arg(args, unsigned long long);
	num = ft_long_hextoa(type);
	if (!num)
		return (-1);
	while (num[i])
	{
		if (write(1, &num[i], 1) == -1)
			return (free(num), -1);
		i++;
	}
	free (num);
	return (i + 2);
}

int	write_number(va_list args)
{
	ssize_t			temp;
	int				type;
	int				i;
	char			*num;

	i = 0;
	temp = 0;
	type = va_arg(args, int);
	num = ft_itoa(type);
	if (!num)
		return (-1);
	while (num[i])
	{
		temp = write(1, &num[i], 1);
		if (temp == -1)
			return (free(num), -1);
		i++;
	}
	free (num);
	return (i);
}

int	write_unsigned(va_list args)
{
	ssize_t			temp;
	unsigned int	type;
	int				i;
	char			*num;

	i = 0;
	temp = 0;
	type = va_arg(args, unsigned int);
	num = ft_utoa(type);
	if (!num)
		return (-1);
	while (num[i])
	{
		temp = write(1, &num[i], 1);
		if (temp == -1)
			return (free(num), -1);
		i++;
	}
	free (num);
	return (i);
}
