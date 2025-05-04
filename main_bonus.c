/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:30:31 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/05 01:18:56 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_error(char *error_explained, char *cmd, int error_code)
{
	if(cmd == NULL)
		ft_putstr_fd(error_explained, STDERR_FILENO);
	else
	{
		ft_putstr_fd(error_explained, STDERR_FILENO);
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

void	ft_error(t_pipe *pipe, char *error_explained, int cmd_pos, int error_code)
{
	if (pipe->cmds)
		free_matrix(pipe->cmds);
	if (pipe->cmd_routes)
		free_matrix(pipe->cmd_routes);
	if (cmd_pos < 0)
		print_error(error_explained, NULL, error_code);
	else
		print_error(error_explained, pipe->cmds[cmd_pos], error_code);
}

char	*find_route(char *instruction, char *path)
{
	char	**routes;
	char	*route;
	char	*cmd_route;
	int		i;

	routes = ft_split(path, ':');
	if (!routes)
		return (0);
	i = 0;
	while (routes[i])
	{
		route = ft_strjoin(routes[i], "/");
		cmd_route = ft_strjoin(route, instruction);
		free(route);
		if (access(cmd_route, F_OK) == 0)
		{
			free_matrix(routes);
			return (cmd_route);
		}
		free(cmd_route);
		i++;
	}
	free_matrix(routes);
	return (NULL);
}

char	*get_route(char *cmd, char **envp)
{
	int		i;
	int		in_line;
	char	**instructions;
	char	*cmd_route;

	i = 0;
	in_line = -1;
	while (envp[i] && in_line == -1)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			in_line = i;
		i++;
	}
	if (in_line == -1)
		print_error("Variable de entorno 'PATH' no encontrada", NULL, 127);
	instructions = ft_split(cmd, ' ');
	if (!instructions)
		return (NULL);
	cmd_route = find_route(instructions[0], &envp[in_line][5]);
	free_matrix(instructions);
	if (!cmd_route)
		return (NULL);
	return (cmd_route);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipe;
	int		i;

	if (argc < 5)
		print_error("Número de argumentos insuficiente\n", NULL, 1);
	i = -1;
	pipe.cmd_nbr = argc - 3; // Descontando ejecutable + archivo in y out
	pipe.cmds = (char **)ft_calloc(pipe.cmd_nbr, sizeof(char *));
	if(!pipe.cmds)
		print_error
	while (++i < pipe.cmd_nbr)
	{
		pipe.cmds[i] = ft_strdup(argv[pipe.cmd_nbr + i]);
		if (!pipe.cmds[i])
			ft_error(&pipe, "Error reservando memoria\n", NULL, 127);
		pipe.cmd_routes[i] = get_route(pipe.cmds[i], envp);
		if (!pipe.cmd_routes[i])
			ft_error(&pipe, "No se encontró el comando: ", i, 127);
	}
	pipe.env = envp;
	pipe.files[0] = argv[1];
	pipe.files[1] = argv[argc - 1];
	pipex(&pipe);
	free(pipe.cmd_routes);
	return (0);
}
