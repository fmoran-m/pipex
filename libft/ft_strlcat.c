/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:13:24 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/06 13:50:17 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	original_src;
	size_t	original_dest;
	size_t	k;

	if ((!dst || !src) && dstsize == 0)
		return (0);
	original_src = ft_strlen(src);
	original_dest = ft_strlen(dst);
	k = original_dest;
	if (dstsize == 0)
		return (original_src + dstsize);
	while (*src && k < dstsize - 1)
	{
		dst[k] = *src;
		k++;
		src++;
	}
	dst[k] = 0;
	if (dstsize <= original_dest)
		return (original_src + dstsize);
	else
		return (original_src + original_dest);
}
