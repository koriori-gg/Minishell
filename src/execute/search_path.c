/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:44 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:33:45 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_path(char **environ, char *line)
{
	int		i;

	i = 0;
	while (environ[i] && ft_strncmp("PATH=", environ[i], 5) != 0)
		i++;
	if (!environ[i])
	{
		builtin_error(line, NULL, "No such file or directory");
		exit(COMMAND_ERROR);
	}
	return (environ[i]);
}

static char	**split_path(char *environ)
{
	char	**path;

	path = ft_split(&environ[5], ':');
	if (!path)
		fatal_error("split_path");
	return (path);
}

static void	join_path(char **path, char *line)
{
	int		i;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
		{
			free_double_pointer(path);
			fatal_error("join_path");
		}
		free(temp);
		temp = path[i];
		path[i] = ft_strjoin(path[i], line);
		free(temp);
		if (!path[i])
		{
			free_double_pointer(path);
			fatal_error("join_path");
		}
		i++;
	}
}

static char	*get_accessible_path(char **path)
{
	char	*accessible_path;
	int		i;

	i = 0;
	while (path[i])
	{
		if (exists_file(path[i]) && is_execrable(path[i]))
		{
			accessible_path = ft_strdup(path[i]);
			if (!accessible_path)
			{
				free_double_pointer(path);
				fatal_error("get_accessible_path");
			}
			free_double_pointer(path);
			return (accessible_path);
		}
		i++;
	}
	free_double_pointer(path);
	return (NULL);
}

char	*search_path(char *line, char **environ)
{
	char	*path;
	char	**split_paths;
	char	*accessible_path;

	if (exists_file(line) && is_execrable(line))
		return (line);
	path = extract_path(environ, line);
	split_paths = split_path(path);
	join_path(split_paths, line);
	accessible_path = get_accessible_path(split_paths);
	if (!accessible_path)
		return (NULL);
	return (accessible_path);
}
