/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:30:31 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/11 21:38:17 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_matrix(char *matrix_name, char **matrix_content)
{
	int	i;

	i = 0;
	while (matrix_content[i])
	{
		printf("%s n%d = %s\n", matrix_name, i + 1, matrix_content[i]);
		i++;
	}
	return;
}

void	print_struct(t_pipe *piped)
{
	printf("PRINT STRUCT\n");
	if (piped->here_doc)
	{
		printf(">>> here_doc = true && delimiter = %s\n", piped->delimiter);
		printf(">>> heredoc_pipe_fds = %dd && %d\n", piped->heredoc_pipe_fds[0], piped->heredoc_pipe_fds[1]);
	}
	else
		printf(">>> infile = %s\n", piped->filein);
	printf(">>> outfile = %s\n", piped->fileout);
	printf(">>> commands number = %d\n", piped->cmd_nbr);
	print_matrix(">>> cmd", piped->cmds);
	print_matrix(">>> cmd_route", piped->cmd_routes);
	printf("\n\n\n");
	return;
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

void	print_error(t_pipe *piped, char *error_msg, int cmd_pos, int error_code)
{
	if (cmd_pos == -1)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	else
	{
		ft_putstr_fd(error_msg, STDERR_FILENO);
		ft_putstr_fd(piped->cmds[cmd_pos], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	exit(error_code);
}

void	pipex_error(t_pipe *piped, char *error_msg, int cmd_pos, int error_code)
{
	if (piped->cmds)
		free_matrix(piped->cmds);
	if (piped->cmd_routes)
		free_matrix(piped->cmd_routes);
	print_error(piped, error_msg, cmd_pos, error_code);
}
