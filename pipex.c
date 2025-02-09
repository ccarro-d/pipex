/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/09 22:24:09 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd1(char **argv, char **env, char *cmd1_route, int *pipe_fd)
{
	char	**cmd1;
	char	*filein;
	int		fd_filein;
	int		pid;

	cmd1 = ft_split(argv[2], ' ');
	filein = argv[1];
	fd_filein = open(filein, O_RDONLY);
	if (fd_filein < 0)
		print_error("No se pudo abrir el archivo de entrada", 255);
	close(pipe_fd[0]);
	dup2(fd_filein, STDIN_FILENO) close(fd_filein);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	if (execve(cmd1_route, cmd1, env) == -1)
	{
		free(cmd1);
		free(cmd1_route);
		print_error("Error al ejecutar el primer comando", 255);
	}
	else
		free(cmd1);
	return ;
}

void	exec_cmd2(char **argv, char **env, char *cmd2_route, int *pipe_fd)
{
	char	**cmd2;
	char	*fileout;
	int		fd_fileout;
	int		pid;

	cmd2 = ft_split(argv[3], ' ');
	fileout = argv[4];
	fd_fileout = open(fileout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_fileout < 0)
		print_error("No se pudo abrir el archivo de entrada", 255);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO) close(pipe_fd[0]);
	dup2(fd_fileout, STDOUT_FILENO);
	close(fd_fileout);
	if (execve(cmd2_route, cmd2, env) == -1)
	{
		free(cmd2);
		free(cmd2_route);
		print_error("Error al ejecutar el segundo comando", 255);
	}
	else
		free(cmd2);
	return ;
}

void	pipex(char **argv, char **evnp.char *cmd1_route, char *cmd2_route)
{
	int		pipe_fd[2];
	int		status;
	pid_t	cmd1;
	pid_t	cmd2;

	pipe(pipe_fd);
	if (pipe_fd == -1)
		print_error("No se puedo crear el pipe", 255);
	cmd1 = fork();
	if (cmd1 < 0)
		print_error("Error iniciando subproceso 1",
			255) if (cmd1 == 0) exec_cmd1(argv, envp, cmd1_route, pipe_fd);
	cmd2 = fork();
	if (cmd2 < 0)
		print_error("Error iniciando subproceso 2",
			255) if (cmd1 == 0) exec_cmd1(argv, envp, cmd2_route, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(cmd1, NULL, 0);
	waitpid(cmd2, NULL, 0);
	return ;
}

//./pipex archvivo1 "ls -l" "wc" archivo2