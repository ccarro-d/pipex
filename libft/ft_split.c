/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:15:40 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/10 21:00:01 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countsubs(const char *s, char c)
{
	int	subs;
	int	i;

	subs = 0;
	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			subs++;
			while (s[i] == c)
			{
				i++;
			}
		}
		else
			i++;
	}
	subs += 1;
	return (subs);
}

static void	ft_free(char **arr, int mark)
{
	int	sub;

	sub = 0;
	while (sub < mark)
	{
		free(arr[sub]);
		sub++;
	}
	free(arr);
	return ;
}

static void	ft_createsubs(char *str, char **arr, char c, int subs)
{
	int		j;
	char	*k;

	j = 0;
	if ((subs > 0) && *str)
	{
		while (j < (subs - 1))
		{
			k = ft_strchr(str, c);
			arr[j] = ft_substr(str, 0, k - str);
			if (!arr[j])
			{
				ft_free(arr, j);
				return ;
			}
			while (*k == c)
				k++;
			str = k;
			j++;
		}
		arr[j] = ft_strdup(str);
		arr[++j] = 0;
	}
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	trm[2];
	char	**arr;
	int		subs;

	if (!s)
		return (0);
	trm[0] = c;
	trm[1] = 0;
	str = ft_strtrim(s, trm);
	if (!str)
		return (0);
	subs = ft_countsubs(str, c);
	arr = (char **)ft_calloc(subs + 1, sizeof(char *));
	if (!arr)
		return (0);
	ft_createsubs(str, arr, c, subs);
	free(str);
	return (arr);
}
