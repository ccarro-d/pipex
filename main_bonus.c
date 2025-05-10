/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:30:31 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/10 13:42:31 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	get_cmds_and_routes(char **argv, t_pipe *piped)
{
	int	i;

	i = 0;
	while (++i < piped->cmd_nbr)
	{
		piped->cmds[i] = ft_strdup(argv[piped->cmd_nbr + i + 2]);
		if (!piped->cmds[i])
			ft_error(&piped, "Error reservando memoria\n", NULL, 127);
		piped->cmd_routes[i] = get_route(piped->cmds[i], piped->env);
		if (!piped->cmd_routes[i])
			ft_error(&piped, "No se encontró el comando: ", i, 127);
		i++;
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	piped;

	if (argc < 5)
		print_error("Número de argumentos insuficiente\n", NULL, 1);
	piped.cmd_nbr = argc - 3; // Descontando ejecutable + archivo in y out
	piped.cmds = (char **)ft_calloc(piped.cmd_nbr, sizeof(char *));
	if (!piped.cmds)
		print_error("Error reservando memoria\n", NULL, 1);
	piped.cmd_routes = (char **)ft_calloc(piped.cmd_nbr, sizeof(char *));
	if (!piped.cmd_routes)
		print_error("Error reservando memoria\n", NULL, 1);
	piped.env = envp;
	get_cmds_and_routes(argv, &piped);
	piped.filein = argv[1];
	piped.fileout = argv[argc - 1];
	//pipex(&piped);
	free_matrix(piped.cmds);
	free_matrix(piped.cmd_routes);
	return (0);
}
