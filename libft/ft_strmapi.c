/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:26:24 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/01/31 15:23:47 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	char	*str;

	if (!s || !f)
		return (0);
	i = ft_strlen(s);
	j = 0;
	str = (char *)ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (0);
	while (i > 0)
	{
		str[j] = f(j, s[j]);
		j++;
		i--;
	}
	str[j] = 0;
	return (str);
}
