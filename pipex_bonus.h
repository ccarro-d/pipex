/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:36:17 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/05 00:47:14 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

// Structure
typedef struct s_pipe
{
	int		cmd_nbr;
	char	**cmds;
	char	**cmd_routes;
	char	*files[2];
	char	**env;
	int		pipe_fds[2];
	pid_t	*cmd_ids;
}	t_pipe;

// Functions
void	print_error(char *error_explained, char *cmd, int error_code);
void	free_matrix(char **matrix);
char	*find_route(char *instruction, char *path);
char	*get_route(char *cmd, char **envp);
void	free_routes(char **cmd_routes);
void	pipex_error(char **cmd_routes, char *error_explained, char *cmd, int error_code);
void	exec_cmd1(char **argv, char **env, char **cmd_routes, int *pipe_fd);
void	exec_cmd2(char **argv, char **env, char **cmd_routes, int *pipe_fd);
void	pipex(char **argv, char **envp, char *cmd1_route, char *cmd2_route);

#endif