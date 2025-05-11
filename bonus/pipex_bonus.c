/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/12 00:25:05 by cesar            ###   ########.fr       */
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
	close(piped->main_pipe_fds[0]);
	dup2(fd_filein, STDIN_FILENO);
	close(fd_filein);
	dup2(piped->main_pipe_fds[1], STDOUT_FILENO);
	close(piped->main_pipe_fds[1]);
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
	close(piped->main_pipe_fds[1]);
	dup2(piped->main_pipe_fds[0], STDIN_FILENO);
	close(piped->main_pipe_fds[0]);
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
	dup2(piped->main_pipe_fds[0], STDIN_FILENO);
	close(piped->main_pipe_fds[0]);
	dup2(piped->main_pipe_fds[1], STDOUT_FILENO);
	close(piped->main_pipe_fds[1]);
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
	pid_t	*cmd_ids;
	int		i;
	piped->cmds = (char **)ft_calloc(piped->cmd_nbr + 1, sizeof(char *));
	piped->main_pipe_fds = (int **)malloc(sizeof(int *) * piped->cmd_nbr);
	if (!cmd_ids)
		pipex_error(piped, "No se pudo reservar memoria para cmd_ids", -1, 1);
	if (pipe(piped->main_pipe_fds) == -1)
		pipex_error(piped, "No se pudo crear el pipe", -1, errno);
	cmd_ids = (pid_t *)malloc(sizeof(pid_t) * piped->cmd_nbr);
	if (!cmd_ids)
		pipex_error(piped, "No se pudo reservar memoria para cmd_ids", -1, 1);
	i = -1;
		while (++i < piped->cmd_nbr)
	{
		cmd_ids[i] = fork();
		if (cmd_ids[i] < 0)
			pipex_error(piped, "Error iniciando subproceso: ", i, errno);
		if (cmd_ids[i] == 0)
			exec_cmd(piped, i);
	}
	close(piped->main_pipe_fds[0]);
	close(piped->main_pipe_fds[1]);
	i = -1;
	while (++i < piped->cmd_nbr)
		waitpid(cmd_ids[i], NULL, 0);
	free(cmd_ids);
}
//  Ejemplo usando el operador pipe:	grep x infile.txt | wc > outfile.txt
//  Ejemplo usando el programa pipex:	./pipex "infile.txt" "grep x" "wc" "outfile.txt"
