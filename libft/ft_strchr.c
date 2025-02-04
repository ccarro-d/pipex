/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:39:14 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/01/31 15:23:57 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;

	chr = c;
	while (*s)
	{
		if (*s == chr)
		{
			return ((char *)s);
		}
		s++;
	}
	if (chr == '\0')
	{
		return ((char *)s);
	}
	return (0);
}
