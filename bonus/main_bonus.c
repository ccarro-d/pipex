/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:30:31 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/05/13 20:23:53 by ccarro-d         ###   ########.fr       */
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
		print_error(NULL, "Variable de entorno 'PATH' no encontrada", -1, 127);
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
	int	first_cmd_pos;
	int	i;

	piped->cmds = (char **)ft_calloc(piped->cmd_nbr + 1, sizeof(char *));
	if (!piped->cmds)
		print_error(NULL, "Error reservando memoria\n", -1, 1);
	piped->cmd_routes = (char **)ft_calloc(piped->cmd_nbr + 1, sizeof(char *));
	if (!piped->cmd_routes)
		print_error(NULL, "Error reservando memoria\n", -1, 1);
	if (!piped->here_doc)
		first_cmd_pos = 2;
	else
		first_cmd_pos = 3;
	i = -1;
	while (++i < piped->cmd_nbr)
	{
		piped->cmds[i] = ft_strdup(argv[i + first_cmd_pos]);
		if (!piped->cmds[i])
			print_error(piped, "Error reservando memoria para cmd \n", i, 127);
		piped->cmd_routes[i] = get_route(piped->cmds[i], piped->env);
		if (!piped->cmd_routes[i])
			print_error(piped, "No se encontró el comando: ", i, 127);
	}
	piped->cmds[i] = NULL;
	piped->cmd_routes[i] = NULL;
}

void	appropiate_input(t_pipe *piped, char **argv)
{
	char	*line;
	int		is_delimiter;

	if (!piped->here_doc)
	{
		piped->filein = argv[1];
		return ;
	}
	if (pipe(piped->heredoc_pipe_fds) == -1)
		pipex_error(piped, "No se pudo crear el here_doc pipe", -1, errno);
	pipe(piped->heredoc_pipe_fds);
	is_delimiter = 0;
	while (!is_delimiter)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(line, piped->delimiter, ft_strlen(piped->delimiter)) == 0)
			is_delimiter = 1;
		else
		{
			write(piped->heredoc_pipe_fds[1], line, ft_strlen(line));
			if (line[ft_strlen(line) - 1] != '\n')
				write(piped->heredoc_pipe_fds[1], "\n", 1);
		}
		free (line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	piped;

	if (argc < 5)
		print_error(NULL, "Número de argumentos insuficiente\n", -1, 1);
	if (ft_strncmp(argv[1], "here_doc", 3) == 0)
	{
		piped.here_doc = 1;
		piped.delimiter = argv[2];
		piped.cmd_nbr = argc - 4; // Descontando ejecutable + here_doc + limitador + archivo out
	}
	else
	{
		piped.here_doc = 0;
		piped.delimiter = NULL;
		piped.cmd_nbr = argc - 3; // Descontando ejecutable + archivo in y out
	}
	piped.env = envp;
	get_cmds_and_routes(argv, &piped);
	appropiate_input(&piped, argv);
	piped.fileout = argv[argc - 1];
	print_struct(&piped); // para debugging
	pipex(&piped);
	free_matrix(piped.cmds);
	free_matrix(piped.cmd_routes);
	return (0);
}
