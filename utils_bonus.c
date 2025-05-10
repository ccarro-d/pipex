/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:30:31 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/10 13:07:17 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_error(char *error_msg, char *cmd, int error_code)
{
	if (cmd == NULL)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	else
	{
		ft_putstr_fd(error_msg, STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);

	}
	exit(error_code);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	ft_error(t_pipe *pipe, char *error_msg, int cmd_pos, int error_code)
{
	if (pipe->cmds)
		free_matrix(pipe->cmds);
	if (pipe->cmd_routes)
		free_matrix(pipe->cmd_routes);
	if (cmd_pos < 0)
		print_error(error_msg, NULL, error_code);
	else
		print_error(error_msg, pipe->cmds[cmd_pos], error_code);
}

void	pipex_error(t_pipe *piped, char *error_msg, int cmd_pos, int error_code)
{
	free_matrix(piped->cmds);
	free_matrix(piped->cmd_routes);
	print_error(error_msg, piped->cmds[cmd_pos], error_code);
}
