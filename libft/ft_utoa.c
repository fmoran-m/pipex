/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:25:04 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/11/13 18:03:33 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	invert(char *str)
{
	int		a;
	int		z;
	char	temp;

	a = 0;
	z = ft_strlen(str) - 1;
	while (a < z)
	{
		temp = str[a];
		str[a] = str[z];
		str[z] = temp;
		a++;
		z--;
	}
}

static char	*reserve(unsigned int n)
{
	int		nr;
	char	*str;

	nr = 0;
	while (n != 0)
	{
		n = n / 10;
		nr++;
	}
	str = (char *)malloc(nr * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	return (str);
}

static void	copy_string(unsigned int n, char *str)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		str[i] = (n % 10);
		if (str[i] < 0)
			str[i] = str[i] * -1;
		str[i] = str[i] + 48;
		n = n / 10;
		i++;
	}
	str[i] = 0;
}

char	*ft_utoa(unsigned int n)
{
	char	*str;

	if (n == 0)
	{
		str = ft_strdup("0");
		return (str);
	}
	str = reserve(n);
	if (str == NULL)
		return (NULL);
	copy_string(n, str);
	invert(str);
	return (str);
}
