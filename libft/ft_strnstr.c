/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 22:20:32 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/01/31 15:23:44 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (!haystack && !len)
		return (0);
	if (ft_strlen(needle) == 0 || haystack == needle)
		return ((char *)haystack);
	while (haystack[i] != '\0' && len > i)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && len > (i + j)
			&& haystack[i + j] != '\0')
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
