/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:10:08 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/01/31 15:23:24 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long n)
{
	int		i;
	long	j;

	i = 0;
	if (n > 0)
		j = n;
	else
	{
		j = -n;
		i++;
	}
	while (j > 0)
	{
		i++;
		j = j / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	long	j;
	char	*str;

	j = (long)n;
	i = ft_intlen(j);
	str = (char *)ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (0);
	if (j < 0)
	{
		str[0] = 45;
		j *= -1;
	}
	str[i--] = 0;
	if (j == 0)
		str[0] = 48;
	while (j > 0)
	{
		str[i--] = j % 10 + 48;
		j = j / 10;
	}
	return (str);
}
