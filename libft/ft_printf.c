/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:51:53 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/12/04 14:26:12 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_type(char const *format, int i, va_list args)
{
	int	counter;

	counter = 0;
	if (format[i] == 'c')
		counter = write_char(args);
	else if (format[i] == 's')
		counter = write_string(args);
	else if (format[i] == 'p')
		counter = write_pointer_address(args);
	else if (format[i] == 'd' || format[i] == 'i')
		counter = write_number(args);
	else if (format[i] == 'u')
		counter = write_unsigned(args);
	else if (format[i] == 'x')
		counter = write_lower_hex(args);
	else if (format[i] == 'X')
		counter = write_upper_hex(args);
	else if (format[i] == '%')
		counter = write_module();
	return (counter);
}

static int	count_bytes(char const *format, va_list args, int counter)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			temp = check_type(format, i + 1, args);
			if (temp == -1)
				return (-1);
			counter = counter + temp;
			i = i + 2;
		}
		else
		{
			temp = write(1, &format[i], 1);
			if (temp == -1)
				return (-1);
			i++;
			counter++;
		}
	}
	return (counter);
}

int	ft_printf(char const *format, ...)
{
	va_list		args;
	int			counter;

	if (!format)
		return (-1);
	counter = 0;
	va_start(args, format);
	counter = count_bytes(format, args, counter);
	va_end(args);
	return (counter);
}
