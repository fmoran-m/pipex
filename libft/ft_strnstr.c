/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:22:18 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/05 18:25:09 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	temp;

	i = 0;
	k = 0;
	if (((!h || !n) && len == 0) || (ft_strlen(h) < ft_strlen(n)))
		return (0);
	if (*n == '\0')
		return ((char *)h);
	while (*h != '\0' && i < len)
	{
		temp = i;
		while (h[i] && n[k] && h[i] == n[k] && i < len)
		{
			i++;
			k++;
		}
		if (n[k] == '\0')
			return ((char *)h + temp);
		i = temp;
		k = 0;
		i++;
	}
	return (0);
}
