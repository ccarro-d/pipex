/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:50:45 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/10 19:08:10 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX FOPEN_MAX
# endif

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

// UTILS FUNCTIONS
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
void	*gnl_calloc(size_t count, size_t size);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strjoin(char const *s1, char const *s2);

// GNL FUNCTIONS
char	*ft_stash(char *stash_read, size_t stash_len, size_t break_pos);
char	*ft_next_line(char *line_read, size_t break_pos);
char	*ft_read_line(int fd, char *stash);
char	*ft_free(char *stash);
char	*get_next_line(int fd);

#endif
