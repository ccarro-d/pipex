/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:53:03 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/01/31 15:23:53 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	catlen;
	size_t	j;

	if ((src == 0 || dst == 0) && dstsize == 0)
		return (0);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	catlen = dstlen + srclen;
	j = 0;
	if (dstsize <= 0)
	{
		return (srclen);
	}
	if (dstsize <= dstlen)
	{
		return (dstsize + srclen);
	}
	while (src[j] != '\0' && dstlen < (dstsize - 1) && dst != src)
	{
		dst[dstlen++] = src[j++];
	}
	dst[dstlen] = '\0';
	return (catlen);
}
