/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:42:22 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/06 13:56:11 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	first(char const *s1, char const *set)
{
	size_t	a;
	size_t	i;

	a = 0;
	i = 0;
	while (set[i])
	{
		if (set[i] == s1[a] && s1[a])
		{
			a++;
			i = -1;
		}
		i++;
	}
	return (a);
}

static int	last(char const *s1, char const *set)
{
	int	z;
	int	i;

	i = 0;
	if (ft_strlen(s1) > 0)
		z = ft_strlen(s1) - 1;
	else
		z = 0;
	while (set[i])
	{
		if (set[i] == s1[z] && z >= 0)
		{
			z--;
			i = -1;
		}
		i++;
	}
	return (z);
}

static char	*control_error(char *ptr)
{
	if (ptr == 0)
		return (0);
	ptr[0] = 0;
	return (ptr);
}

static char	*allocate(const char *s1, char *ptr, int a, int z)
{
	int	i;

	i = 0;
	while (a <= z)
	{
		ptr[i] = s1[a];
		i++;
		a++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		a;
	int		z;	
	char	*ptr;

	if (!s1)
		return (0);
	a = first(s1, set);
	z = last(s1, set);
	if (!s1[a] || z < 0)
	{
		ptr = (char *)malloc(1);
		ptr = control_error(ptr);
		return (ptr);
	}
	ptr = (char *)malloc((z - a + 2));
	if (ptr == 0)
		return (0);
	ptr = allocate(s1, ptr, a, z);
	return (ptr);
}
