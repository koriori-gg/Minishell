/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:37 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:33:37 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_execrable(char *path)
{
	if (access(path, X_OK) == 0)
		return (true);
	else
		return (false);
}

bool	exists_file(char *path)
{
	if (access(path, F_OK) == 0)
		return (true);
	else
		return (false);
}

bool	is_file(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (false);
	if (S_ISREG(st.st_mode))
		return (true);
	return (false);
}

bool	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (false);
	if (S_ISDIR(st.st_mode))
		return (true);
	return (false);
}
