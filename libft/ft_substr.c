/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:42:05 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/04 16:00:35 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*pointer(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			k;
	char			*new;

	i = 0;
	k = 0;
	while (i < start)
		i++;
	while (s[i] && k < len)
	{
		k++;
		i++;
	}
	new = (char *)malloc(k * sizeof(char) + 1);
	if (new == NULL)
		return (NULL);
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*new;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		new = (char *)malloc(1);
		if (new == NULL)
			return (NULL);
		*new = '\0';
		return (new);
	}
	new = pointer(s, start, len);
	if (new == NULL)
		return (NULL);
	while (s[start] && i < len)
	{
		new[i] = s[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}
