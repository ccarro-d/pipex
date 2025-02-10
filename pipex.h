/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:36:17 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/10 18:34:16 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define BHBLK "\e[1;90m"
# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"
# define END "\e[0m"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define READ_END 0  /*index pipe extremo escritura*/
# define WRITE_END 1 /*index pipe extremo lectura*/

# include "libft/libft.h"

// Functions
void	print_error(char *error_explained, int error_code);
void	free_matrix(char **matrix);
char	*find_route(char *instruction, char *path);
char	*get_route(char *cmd, char **envp);
void	free_routes(char **cmd_routes);
void	pipex_error(char **cmd_routes, char *error_explained, int error_code);
void	exec_cmd1(char **argv, char **env, char **cmd_routes, int *pipe_fd);
void	exec_cmd2(char **argv, char **env, char **cmd_routes, int *pipe_fd);
void	pipex(char **argv, char **envp, char *cmd1_route, char *cmd2_route);

#endif