/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:36:17 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/10 14:04:05 by ccarro-d         ###   ########.fr       */
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
	char	*filein;
	char	*fileout;
	char	**env;
	int		pipe_fds[2];
	pid_t	*cmd_ids;
}	t_pipe;

// main.c functions
char	*find_route(char *instruction, char *path);
char	*get_route(char *cmd, char **envp);
void	get_cmds_and_routes(char **argv, t_pipe *pipe);

// pipex.c functions
void	pipex(t_pipe *piped);
void	exec_cmd(t_pipe *piped, int *pipe_fds, int cmd_pos);
void	exec_intermediate_cmd(t_pipe *piped, int *pipe_fds, int cmd_pos);
void	exec_last_cmd(t_pipe *piped, int *pipe_fds, int cmd_pos);
void	exec_first_cmd(t_pipe *piped, int *pipe_fds, int cmd_pos);

//utils.c functions
void	print_error(char *error_msg, char *cmd, int error_code);
void	free_matrix(char **matrix);
void	ft_error(t_pipe *pipe, char *error_msg, int cmd_pos, int error_code);
void	pipex_error(t_pipe *piped, char *error_msg, int cmd_pos, int error_code);

#endif
