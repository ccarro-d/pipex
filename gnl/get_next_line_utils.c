/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:43:34 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/16 21:16:33 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	char	chr;

	if (!s)
	{
		return (0);
	}
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

void	*gnl_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(count * size);
	if (!str)
		return (0);
	i = 0;
	while (i < count * size)
		str[i++] = '\0';
	return ((void *)str);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (len == 0 || start >= gnl_strlen(s))
		str = (char *)gnl_calloc(1, sizeof(char));
	else if (len >= (gnl_strlen(s) - start))
	{
		str = (char *)gnl_calloc(gnl_strlen(s) - start + 1, sizeof(char));
		if (!str)
			return (0);
		while (s[start] != '\0')
			str[i++] = s[start++];
	}
	else
	{
		str = (char *)gnl_calloc(len + 1, sizeof(char));
		if (!str)
			return (0);
		while (len--)
			str[i++] = s[start++];
	}
	return (str);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = gnl_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (0);
	str = (char *)gnl_calloc(gnl_strlen(s1) + gnl_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	free((void *)s1);
	return (str);
}
