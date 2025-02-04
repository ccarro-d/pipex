/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:38:44 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/01/31 15:23:56 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*s2;
	int		i;
	int		j;

	i = ft_strlen(s1);
	str = (char *)malloc(i + 1);
	if (!str)
	{
		return (0);
	}
	j = 0;
	s2 = (char *)s1;
	while (s2[j] != '\0')
	{
		str[j] = s2[j];
		j++;
	}
	str[i] = '\0';
	return (str);
}
