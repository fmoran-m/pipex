/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:59:11 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/06 13:20:06 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tonbr(int n, int fd, int neg_flag)
{
	int	a[11];
	int	i;

	i = 0;
	while (n > 0)
	{
		a[i] = (n % 10) + 48;
		n = n / 10;
		i++;
	}
	if (neg_flag == 1)
		a[i] = '-';
	else
		i--;
	while (i >= 0)
	{
		write(fd, &a[i], 1);
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	neg_flag;

	if (fd < 0)
		return ;
	neg_flag = 0;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
	{
		neg_flag = 1;
		n = n * -1;
	}
	ft_tonbr(n, fd, neg_flag);
}
