/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:30:31 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/09 22:24:16 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *error_explain, int error_code)
{
	ft_putstr_fd(error_explain, STDERR_FILENO);
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
			// printf("    RUTA '%s' = %s\n", instruction, cmd_route);
				//TODO: comentar
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
	in_line = i;
	while (envp[i] && in_line == 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			in_line = i;
		i++;
	}
	if (in_line == 0)
		print_error("No se encontró la variable de entorno 'PATH'", 255);
			// TODO: revisar código error
	instructions = ft_split(cmd, ' ');
	if (!instructions)
		return (NULL);
	cmd_route = find_route(instructions[0], &envp[in_line][5]);
	if (!cmd_route)
		return (NULL);
	free_matrix(instructions);
	return (cmd_route);
}

int	main(int argc, char **argv, char **envp)
// evnp es un tipo de input que puede tener main que equivale al contenido del comando "env" en la consola
{
	char *cmd1;
	char *cmd2;
	char *cmd1_route;
	char *cmd2_route;

	(void)argc;
	if (argc != 5)                                           // ejecutable
		+ archivo 1 + comando 1 + comando 2 + archivo 2 == 5
		print_error("Número de argumentos incorrecto", 255);
			// TODO: revisar código error
	cmd1 = argv[2];
	cmd2 = argv[3];
	cmd1_route = get_route(cmd1, envp);
	cmd2_route = get_route(cmd2, envp);
	if (!cmd1_route || !cmd2_route)
		print_error("Comando no encontrado", 255); // TODO: revisar código error
	// pipex(argv, envp, cmd1_route, cmd2_route);
	free(cmd1_route);
	free(cmd2_route);
	return (0);
}
