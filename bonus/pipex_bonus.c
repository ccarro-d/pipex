/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/13 20:00:12 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_first_cmd(t_pipe *piped, int cmd_pos)
{
	char	**cmd_instr;
	int		fd_filein;

	cmd_instr = ft_split(piped->cmds[cmd_pos], ' ');
	if (!cmd_instr)
		pipex_error(piped, "Error procesando el primer comando", cmd_pos, 2);
	if (!piped->here_doc)
		fd_filein = open(piped->filein, O_RDONLY);
	else
		fd_filein = piped->heredoc_pipe_fds[0];
	if (fd_filein < 0)
	{
		free_matrix(cmd_instr);
		pipex_error(piped, "No pudo abrir archivo de entrada", cmd_pos, errno);
	}
	close(piped->heredoc_pipe_fds[1]);
	close(piped->current_pipe_fds[0]);
	dup2(fd_filein, STDIN_FILENO);
	close(fd_filein);
	dup2(piped->current_pipe_fds[1], STDOUT_FILENO);
	close(piped->current_pipe_fds[1]);
	if (execve(piped->cmd_routes[cmd_pos], cmd_instr, piped->env) == -1)
	{
		free_matrix(cmd_instr);
		pipex_error(piped, "Error ejecutando primer comando", cmd_pos, errno);
	}
}

void	exec_last_cmd(t_pipe *piped, int cmd_pos)
{
	char	**cmd_instr;
	int		fd_fileout;

	cmd_instr = ft_split(piped->cmds[cmd_pos], ' ');
	if (!cmd_instr)
		pipex_error(piped, "Error procesando el último comando", cmd_pos, 2);
	if (!piped->here_doc)
		fd_fileout = open(piped->fileout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd_fileout = open(piped->fileout, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd_fileout < 0)
	{
		free_matrix(cmd_instr);
		pipex_error(piped, "No pudo abrir archivo de salida", cmd_pos, errno);
	}
	dup2(piped->previous_pipe_fd, STDIN_FILENO);
	close(piped->previous_pipe_fd);
	dup2(fd_fileout, STDOUT_FILENO);
	close(fd_fileout);
	if (execve(piped->cmd_routes[cmd_pos], cmd_instr, piped->env) == -1)
	{
		free_matrix(cmd_instr);
		pipex_error(piped, "Error ejecutando último comando", cmd_pos, errno);
	}
}

void	exec_intermediate_cmd(t_pipe *piped, int cmd_pos)
{
	char	**cmd_instr;

	cmd_instr = ft_split(piped->cmds[cmd_pos], ' ');
	if (!cmd_instr)
		pipex_error(piped, "Error procesando comando intermedio", cmd_pos, 2);
	dup2(piped->previous_pipe_fd, STDIN_FILENO);
	close(piped->previous_pipe_fd);
	dup2(piped->current_pipe_fds[1], STDOUT_FILENO);
	close(piped->current_pipe_fds[1]);
	if (execve(piped->cmd_routes[cmd_pos], cmd_instr, piped->env) == -1)
	{
		free_matrix(cmd_instr);
		pipex_error(piped, "Error ejecutando comando intermedio", cmd_pos, errno);
	}
}

void	exec_cmd(t_pipe *piped, int cmd_pos)
{
	if (cmd_pos == 0)
		exec_first_cmd(piped, cmd_pos);
	else if (cmd_pos == piped->cmd_nbr - 1)
		exec_last_cmd(piped, cmd_pos);
	else
		exec_intermediate_cmd(piped, cmd_pos);
}

void	pipex(t_pipe *piped)
{
	//int		current_pipe_fds[2];
	//int		previous_pipe_fd;
	int		cmd_pos;
	//pid_t	cmd_id;

	piped->previous_pipe_fd = -1;
	cmd_pos = -1;
	while (++cmd_pos < piped->cmd_nbr)
	{
		if (cmd_pos < piped->cmd_nbr - 1 && pipe(piped->current_pipe_fds) == -1)
			pipex_error(piped, "No se pudo crear el pipe", -1, errno);
		piped->cmd_id = fork();
		if (piped->cmd_id < 0)
			pipex_error(piped, "Error iniciando subproceso: ", cmd_pos, errno);
		if (piped->cmd_id == 0)
			exec_cmd(piped, cmd_pos);
		if (piped->previous_pipe_fd != -1)
			close(piped->previous_pipe_fd);
		if (piped->here_doc && cmd_pos == 0)
		{
			close(piped->heredoc_pipe_fds[0]);
			close(piped->heredoc_pipe_fds[1]);
		}
		if (cmd_pos < piped->cmd_nbr - 1)
		{
			close(piped->current_pipe_fds[1]);
			piped->previous_pipe_fd = piped->current_pipe_fds[0];
		}
		waitpid(piped->cmd_id, NULL, 0);
	}
}
//  Ejemplo usando el operador pipe:	grep x infile.txt | wc > outfile.txt
//  Ejemplo usando el programa pipex:	./pipex "infile.txt" "grep x" "wc" "outfile.txt"
