/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:23:18 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/01/31 15:23:40 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (0);
	if (len == 0 || start >= ft_strlen(s))
		str = (char *)ft_calloc(1, sizeof(char));
	else if (len >= (ft_strlen(s) - start))
		str = (char *)ft_strdup(&s[start]);
	else
	{
		str = (char *)ft_calloc(len + 1, sizeof(char));
		if (!str)
			return (0);
		ft_strlcpy(str, &s[start], len + 1);
	}
	return (str);
}
