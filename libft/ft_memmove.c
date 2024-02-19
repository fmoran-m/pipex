/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:13:17 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/04 15:34:11 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	const unsigned char	*s;
	unsigned char		*d;

	if (dst == 0 && src == 0)
		return (NULL);
	d = dst;
	s = src;
	i = 0;
	if (s < d)
	{
		while (len-- > 0)
			d[len] = s[len];
		return (d);
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
		return (dst);
	}
}
