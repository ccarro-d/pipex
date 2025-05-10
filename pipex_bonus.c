/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/10 14:02:46 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_first_cmd(t_pipe *piped, int *pipe_fds, int cmd_pos)
{
	char	**cmd_instr;
	int		fd_filein;

	cmd_instr = ft_split(piped->cmds[cmd_pos], ' ');
	if (!cmd_instr)
		pipex_error(piped, "Error procesando el primer comando", cmd_pos, 2);
	fd_filein = open(piped->filein, O_RDONLY);
	if (fd_filein < 0)
	{
		free_matrix(cmd_instr);
		pipex_error(piped, "No pudo abrir archivo de entrada", cmd_pos, errno);
	}
	close(pipe_fds[0]);
	dup2(fd_filein, STDIN_FILENO);
	close(fd_filein);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	if (execve(piped->cmd_routes[cmd_pos], cmd_instr, piped->env) == -1)
	{
		free_matrix(cmd_instr);
		pipex_error(piped, "Error ejecutando primer comando", cmd_pos, errno);
	}
	return ;
}

void	exec_last_cmd(t_pipe *piped, int *pipe_fds, int cmd_pos)
{
	char	**cmd_instr;
	int		fd_fileout;

	cmd_instr = ft_split(piped->cmds[cmd_pos], ' ');
	if (!cmd_instr)
		pipex_error(piped, "Error procesando el último comando", cmd_pos, 2);
	fd_fileout = open(piped->fileout, O_RDONLY);
	if (fd_fileout < 0)
	{
		free_matrix(cmd_instr);
		pipex_error(piped, "No pudo abrir archivo de salida", cmd_pos, errno);
	}
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	dup2(fd_fileout, STDOUT_FILENO);
	close(fd_fileout);
	if (execve(piped->cmd_routes[cmd_pos], cmd_instr, piped->env) == -1)
	{
		free_matrix(cmd_instr);
		pipex_error(piped, "Error ejecutando último comando", cmd_pos, errno);
	}
	return ;
}

void	exec_intermediate_cmd(t_pipe *piped, int *pipe_fds, int cmd_pos)
{
	char	**cmd_instr;

	cmd_instr = ft_split(piped->cmds[cmd_pos], ' ');
	if (!cmd_instr)
		pipex_error(piped, "Error procesando comando intermedio", cmd_pos, 2);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	if (execve(piped->cmd_routes[cmd_pos], cmd_instr, piped->env) == -1)
	{
		free_matrix(cmd_instr);
		pipex_error(piped, "Error ejecutando comando intermedio", cmd_pos, errno);
	}
	return ;
}

void	exec_cmd(t_pipe *piped, int *pipe_fds, int cmd_pos)
{
	if (cmd_pos == 0)
		exec_first_cmd(piped, pipe_fds, cmd_pos);
	else if (cmd_pos == piped->cmd_nbr - 1)
		exec_last_cmd(piped, pipe_fds, cmd_pos);
	else
		exec_intermediate_cmd(piped, pipe_fds, cmd_pos);
	return ;
}

void	pipex(t_pipe *piped)
{
	int		pipe_fds[2];
	pid_t	*cmd_ids;
	int		i;

	if (pipe(pipe_fds) == -1)
		pipex_error(piped, "No se pudo crear el pipe", NULL, errno);
	i = 0;
	while (i < piped->cmd_nbr)
	{
		cmd_ids[i] = fork();
		if (cmd_ids[i] < 0)
			pipex_error(piped, "Error iniciando subproceso:", i, errno);
		if (piped->cmds[i] = 0)
			exec_cmd(piped, pipe_fds, i);
		i++;
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	i = -1;
	while (++i < piped->cmd_nbr)
		waitpid(cmd_ids[i], NULL, 0);
	return ;
}
//  Ejemplo usando el operador pipe:	grep x infile.txt | wc > outfile.txt
//  Ejemplo usando el programa pipex:	./pipex "infile.txt" "grep x" "wc" "outfile.txt"
