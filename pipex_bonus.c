/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/04 23:59:16 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*void	free_routes(char **cmd_routes)
{
	char	*cmd1_route;
	char	*cmd2_route;

	cmd1_route = cmd_routes[0];
	cmd2_route = cmd_routes[1];
	if (cmd1_route)
		free(cmd1_route);
	if (cmd2_route)
		free(cmd2_route);
	return ;
}*/

void	pipex_error(char **cmd_routes, char *error_explained, char *cmd, int error_code)
{
	//free_routes(cmd_routes);
	free_matrix(cmd_routes);
	print_error(error_explained, cmd, error_code);
}

void	exec_cmd1(char **argv, char **env, char **cmd_routes, int *pipe_fds)
{
	char	**cmd1;
	char	*filein;
	int		fd_filein;

	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		pipex_error(cmd_routes, "Error procesando el primer comando", 2);
	filein = argv[1];
	fd_filein = open(filein, O_RDONLY);
	if (fd_filein < 0)
	{
		free_matrix(cmd1);
		pipex_error(cmd_routes, "No pudo abrirse el archivo de entrada", errno);
	}
	close(pipe_fds[0]);
	dup2(fd_filein, STDIN_FILENO);
	close(fd_filein);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	if (execve(cmd_routes[0], cmd1, env) == -1)
	{
		free_matrix(cmd1);
		pipex_error(cmd_routes, "Error al ejecutar el primer comando", errno);
	}
}

void	exec_cmd2(char **argv, char **env, char **cmd_routes, int *pipe_fds)
{
	char	**cmd2;
	char	*fileout;
	int		fd_fileout;

	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
		pipex_error(cmd_routes, "Error procesando el segundo comando", 2);
	fileout = argv[4];
	fd_fileout = open(fileout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_fileout < 0)
	{
		free_matrix(cmd2);
		pipex_error(cmd_routes, "No pudo abrirse el archivo de salida", errno);
	}
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	dup2(fd_fileout, STDOUT_FILENO);
	close(fd_fileout);
	if (execve(cmd_routes[1], cmd2, env) == -1)
	{
		free_matrix(cmd2);
		pipex_error(cmd_routes, "Error al ejecutar el segundo comando", errno);
	}
}

void	pipex(char **envp, char **cmds, char **cmd_routes, char **files)
{
	int		pipe_fds[2];
	pid_t	*cmd_ids;
	int		i;

	if (pipe(pipe_fds) == -1)
		pipex_error(cmd_routes, "No se pudo crear el pipe", NULL, errno);
	i = 0;
	while (i < cmd_nbr)
	{
		cmd_ids[i] = fork();
		if(cmd_ids[i] < 0)
			pipex_error(cmd_routes, "Error iniciando subproceso:", cmds[i], errno);	
		if(cmds[i] = 0) 
			exec_cmd(envp, cmds, cmd_routes, pipe_fds);
		i++;
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	int i = -1;
	while (++i < cmd_nbr)
		waitpid(cmd_ids[i], NULL, 0);
	return ;
}
//  Ejemplo usando el operador pipe:	grep x infile.txt | wc > outfile.txt
//  Ejemplo usando el programa pipex:	./pipex "infile.txt" "grep x" "wc" "outfile.txt"