/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:41:45 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/06 15:52:26 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	t_list	*res;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		res = f(lst->content);
		temp = ft_lstnew(res);
		if (temp == NULL)
		{
			ft_lstclear(&new, del);
			del(res);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}
