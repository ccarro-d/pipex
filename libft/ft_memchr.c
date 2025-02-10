/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:26:44 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/10 20:59:24 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	chr;
	unsigned char	*str;

	chr = c;
	str = (unsigned char *)s;
	while (n)
	{
		if (*str == chr)
		{
			return ((void *)str);
		}
		str++;
		n--;
	}
	return (NULL);
}
