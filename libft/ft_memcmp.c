/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:55:12 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/09/21 18:08:40 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*a1;
	unsigned const char	*a2;

	a1 = s1;
	a2 = s2;
	i = 0;
	while (i < n)
	{
		if (a1[i] != a2[i])
			return ((unsigned int) a1[i] - (unsigned int) a2[i]);
		i++;
	}
	return (0);
}
