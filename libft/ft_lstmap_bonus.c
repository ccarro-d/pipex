/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:59:29 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/01/31 15:24:16 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;

	if (!lst || !f || !del)
		return (0);
	head = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst != 0)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	return (head);
}
