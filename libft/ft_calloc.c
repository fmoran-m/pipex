/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:36:30 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/06 12:53:40 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;
	size_t	total_amount;

	i = 0;
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	total_amount = size * count;
	ptr = malloc(total_amount);
	if (!ptr)
		return (NULL);
	while (i < total_amount)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
