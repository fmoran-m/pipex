/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:07:53 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/06 00:35:45 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, unsigned char c)
{
	int	flag;
	int	i;
	int	n;

	flag = 1;
	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 1)
		{
			n++;
			flag = 0;
		}
		if (s[i] == c)
			flag = 1;
		i++;
	}
	return (n);
}

static int	l(char const *s, unsigned char c, int total)
{
	int	i;

	i = total;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	ft_free_arrays(char **ptr, int i)
{
	int	n;

	n = 0;
	while (n < i)
	{
		free(ptr[n]);
		n++;
	}
	free(ptr);
}

static void	ft_allocate_arrays(char const *s, unsigned char c, char **ptr)
{
	int	i;
	int	j;
	int	total;

	i = 0;
	total = 0;
	while (s[total] == c)
		total++;
	while (i < ft_count_words(s, c))
	{
		j = 0;
		while (s[total] != c && s[total])
		{
			ptr[i][j] = s[total];
			total++;
			j++;
		}
		while (s[total] == c && c != 0)
			total++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	struct s_vars		a;
	char				**ptr;

	a.total = 0;
	a.i = 0;
	if (!s)
		return (NULL);
	ptr = ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	if (!ft_count_words(s, c))
		return (ptr);
	while (a.i < ft_count_words(s, c))
	{
		if (s[a.total] != c)
		{
			ptr[a.i] = ft_calloc(l(s, c, a.total) - a.total + 1, 1);
			if (ptr[a.i++] == NULL)
				return (ft_free_arrays(ptr, a.i), NULL);
			a.total = l(s, c, a.total) - 1;
		}
		a.total++;
	}
	ft_allocate_arrays(s, c, ptr);
	return (ptr);
}
