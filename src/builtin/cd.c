/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:32:28 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/20 23:08:29 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	identify_cd_error(char *arg)
{
	if (errno == ENOTDIR)
		builtin_error("cd", arg, "Not a directory");
	else if (exists_file(arg))
		builtin_error("cd", arg, "Permission denied");
	else
		builtin_error("cd", arg, "No such file or directory");
}

int	builtin_cd(t_env **env, char **argv)
{
	char	path[PATH_MAX];
	char	*homepath;

	if (argv[1])
		ft_strlcpy(path, argv[1], PATH_MAX);
	else
	{
		homepath = get_env_value(*env, "HOME");
		if (!homepath)
		{
			builtin_error("cd", NULL, "HOME not set");
			free(homepath);
			return (1);
		}
		ft_strlcpy(path, homepath, PATH_MAX);
		free(homepath);
	}
	if (chdir(path) == -1)
	{
		identify_cd_error(argv[1]);
		return (1);
	}
	set_env(env, try_strdup("OLDPWD"), get_env_value(*env, "PWD"));
	set_env(env, try_strdup("PWD"), getcwd(NULL, 0));
	return (0);
}
