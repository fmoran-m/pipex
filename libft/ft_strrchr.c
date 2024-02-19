/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:22:32 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/09/21 18:09:04 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ca;
	const char		*first;

	ca = c;
	first = s;
	while (*s)
		s++;
	while (s >= first)
	{
		if (*s == ca)
			return ((char *)s);
		s--;
	}
	return (0);
}
