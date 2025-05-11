/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:43:34 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/16 21:16:03 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *stash)
{
	free (stash);
	stash = NULL;
	return (stash);
}

char	*ft_stash(char *stash, size_t stash_len, size_t break_pos)
{
	size_t	new_stash_size;
	char	*new_stash;

	new_stash_size = stash_len - break_pos;
	if (!new_stash_size || !stash[break_pos])
		return (ft_free(stash));
	new_stash = gnl_substr(stash, break_pos, new_stash_size);
	ft_free(stash);
	if (!new_stash)
		return (NULL);
	return (new_stash);
}

char	*ft_next_line(char *stash, size_t break_pos)
{
	char	*next_line;

	next_line = gnl_substr(stash, 0, break_pos);
	if (!next_line)
		return (NULL);
	return (next_line);
}

char	*ft_read_line(int fd, char *stash)
{
	char	*buf;
	int		bytes_read;

	buf = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!gnl_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read > 0 || (bytes_read == 0 && *buf))
		{
			buf[bytes_read] = '\0';
			stash = gnl_strjoin(stash, buf);
		}
	}
	free (buf);
	if (bytes_read < 0)
		return (ft_free(stash));
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*stash[OPEN_MAX];
	size_t		stash_len;
	size_t		break_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash[fd] = ft_read_line(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	stash_len = gnl_strlen(stash[fd]);
	if (gnl_strchr(stash[fd], '\n'))
		break_pos = gnl_strchr(stash[fd], '\n') - stash[fd] + 1;
	else
		break_pos = stash_len;
	next_line = ft_next_line(stash[fd], break_pos);
	if (!next_line)
		return (ft_free(stash[fd]));
	stash[fd] = ft_stash(stash[fd], stash_len, break_pos);
	return (next_line);
}
