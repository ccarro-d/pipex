/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:44:39 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/01/31 15:23:41 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (!s1 || !set)
		return (0);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != 0)
		i++;
	while (j > i && ft_strchr(set, s1[j]) != 0)
		j--;
	len = j - i + 1;
	str = ft_substr(s1, i, len);
	if (!str)
		return (0);
	return (str);
}
