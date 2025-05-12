/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:36:17 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/12 21:51:33 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <errno.h>
//# include <fcntl.h>
# include <sys/wait.h>

// Structure
typedef struct s_pipe
{
	int		here_doc;
	char	*delimiter;
	int		cmd_nbr;
	char	**cmds;
	char	**cmd_routes;
	char	*filein;
	char	*fileout;
	char	**env;
	int		heredoc_pipe_fds[2];
	int		current_pipe_fds[2];
	int		previous_pipe_fd;
	pid_t	cmd_id;
}	t_pipe;

// main.c functions
char	*find_route(char *instruction, char *path);
char	*get_route(char *cmd, char **envp);
void	get_cmds_and_routes(char **argv, t_pipe *pipe);
void	appropiate_input(t_pipe *piped, char **argv);

// pipex.c functions
void	pipex(t_pipe *piped);
void	exec_cmd(t_pipe *piped, int cmd_pos);
void	exec_intermediate_cmd(t_pipe *piped, int cmd_pos);
void	exec_last_cmd(t_pipe *piped, int cmd_pos);
void	exec_first_cmd(t_pipe *piped, int cmd_pos);

//utils.c functions
void	print_matrix(char *matrix_name, char **matrix_content); // para debugging
void	print_struct(t_pipe *piped); // para debugging
void	free_matrix(char **matrix);
void	print_error(t_pipe *piped, char *error_msg, int cmd_pos, int error_code);
void	pipex_error(t_pipe *piped, char *error_msg, int cmd_pos, int error_code);

#endif
