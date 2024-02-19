/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexatoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:43:09 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/12/13 18:29:56 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isxdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'a' && c <= 'f')
		return (1);
	else if (c >= 'A' && c <= 'F')
		return (1);
	else if (c == 'x' || c == 'X')
		return (1);
	else
		return (0);
}

static void	control_sign(const char *str, int *i, int *flag)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*flag = 1;
		(*i)++;
	}
}

int	ft_atoi_base(const char *str, int base)
{
	int	i;
	int	flag;
	int	acum;

	if (!str)
		return (0);
	i = 0;
	flag = 0;
	acum = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	control_sign(str, &i, &flag);
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while (ft_isxdigit(str[i]))
	{
		if (ft_isdigit(str[i]))
			acum = acum * base + (str[i] - 48);
		else
			acum = acum * base + (ft_toupper(str[i]) - 'A' + 10);
		i++;
	}
	if (flag == 1)
		acum = acum * -1;
	return (acum);
}
