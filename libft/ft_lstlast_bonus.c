/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:07:20 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/01/31 15:23:35 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		i;
	t_list	*aux;

	i = ft_lstsize(lst) - 1;
	aux = lst;
	while (i > 0)
	{
		aux = aux->next;
		i--;
	}
	return (aux);
}
