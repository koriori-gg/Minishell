/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:47 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:33:47 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	identify_dot_argument_error(char *arg, char *path)
{
	if (is_directory(arg) && is_execrable(arg))
	{
		g_minishell.exit_status = FILE_ERROR;
		command_error(arg, "is a directory");
	}
	else if (is_file(arg) && !is_execrable(arg))
	{
		g_minishell.exit_status = FILE_ERROR;
		command_error(arg, "Permission denied");
	}
	else if (!path)
	{
		g_minishell.exit_status = ERROR;
		if (is_directory(arg) && exists_file(path))
			command_error(arg, "Not a directory");
		else
			command_error(arg, "No such file or directory");
	}
	else
	{
		g_minishell.exit_status = COMMAND_ERROR;
		command_error(arg, "command not found");
	}
	exit(g_minishell.exit_status);
}

static void	validate_dot(char **environ, char **argv)
{
	char	*path;

	if (ft_strncmp(argv[0], ".", ft_strlen(argv[0])) == 0)
	{
		if (argv[1])
		{
			path = search_path(argv[1], environ);
			identify_dot_argument_error(argv[1], path);
		}
		g_minishell.exit_status = USAGE_ERROR;
		usage_error(argv[0], "filename [arguments]");
		exit(g_minishell.exit_status);
	}
}

static void	validate_line(char *line, char *path)
{
	if (is_directory(line) && ft_strchr(line, '/'))
	{
		g_minishell.exit_status = FILE_ERROR;
		command_error(line, "is a directory");
	}
	if (is_file(line) && !is_execrable(line) && ft_strchr(line, '/'))
	{
		g_minishell.exit_status = FILE_ERROR;
		command_error(line, "Permission denied");
	}
	if (!exists_file(line) && ft_strchr(line, '/'))
	{
		g_minishell.exit_status = COMMAND_ERROR;
		command_error(line, "No such file or directory");
	}
	if (!path && (!is_directory(line) && errno == ENOTDIR))
	{
		g_minishell.exit_status = FILE_ERROR;
		command_error(line, "Not a directory");
	}
	if (!path || (is_directory(line) && is_execrable(line)))
	{
		g_minishell.exit_status = COMMAND_ERROR;
		command_error(line, "command not found");
	}
}

void	validate_path(char **environ, char **argv, char *path)
{
	if (!argv[0])
	{
		g_minishell.exit_status = COMMAND_ERROR;
		command_error(argv[0], "command not found");
	}
	validate_dot(environ, argv);
	validate_line(argv[0], path);
}
