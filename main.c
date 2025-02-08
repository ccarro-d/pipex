/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:30:31 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/08 14:58:37 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*get_path(char *cmd, char **envp)
{
	char	**instructions;
	int		i;
	int		in_line;
	char	**paths;
	char	*route;
	char	*cmd_in_route;

	i = 0;
	in_line = i;
	while (envp[i] && in_line == 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			in_line = i;
			printf("%s\n", envp[in_line]);
		}
		i++;
	}
	instructions = ft_split(cmd, ' ');
    if (!instructions)
        return (NULL);
	paths = ft_split(&envp[in_line][5], ':');
	i = 0;
	while (paths[i])
	{
		route = ft_strjoin(paths[i], "/");
		cmd_in_route = ft_strjoin(route, instructions[0]);
		free(route);
		if (access(cmd_in_route, F_OK) == 0)
		{
			free(paths);
			printf("    RUTA = %s\n", cmd_in_route);
			return (cmd_in_route);
		}
		free(cmd_in_route);
		i++;
	}
	free_matrix(paths);
    free_matrix(instructions);
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
		// evnp es un tipo de input que puede tener main que equivale al contenido del comando "env" en la consola
{
	char *cmd1;
	char *cmd2;
	char *path_cmd1;
	char *path_cmd2;

	(void)argc;
	/*if (argc != 5) // ejecutable + archivo 1 + comando 1 + comando 2
		+ archivo 2 == 5
		prnt_error()
			// TODO: funcion que imprima error (nº argumentos incorrecto) por el fd=2 (STDERR) y retorne un código de error*/
	cmd1 = argv[2];
	cmd2 = argv[3];
	path_cmd1 = get_path(cmd1, envp);
	path_cmd2 = get_path(cmd2, envp);
	/* if (!path_cmd1 || !path_cmd2)
		prnt_error()
			// TODO: funcion que imprima error (comando no encontrado) por el fd=2 (STDERR) y retorne un código de error*/
	// pipex(argv, envp, path_cmd1, path_cmd2); */
	free(path_cmd1);
	free(path_cmd2);
	return (0);
}
