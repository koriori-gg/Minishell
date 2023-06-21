/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:04 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:33:04 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pwdenv(t_env **env)
{
	char	pwd[PATH_MAX];
	char	*name;

	if (!exists_env(env, "PWD"))
	{
		if (!getcwd(pwd, PATH_MAX))
			fatal_error("init_pwdenv");
		name = try_strdup("PWD");
		set_env(env, name, try_strdup(pwd));
	}
	if (!exists_env(env, "OLDPWD"))
	{
		name = try_strdup("OLDPWD");
		set_env(env, name, NULL);
	}
}

static void	environ_to_env(char **environ, t_env **env)
{
	char		*namelast;
	int			i;
	char		*name;
	char		*value;

	i = 0;
	while (environ[i])
	{
		namelast = ft_strchr(environ[i], '=');
		name = try_strndup(environ[i], namelast - environ[i]);
		value = try_strdup(namelast + 1);
		if (!value && namelast)
			fatal_error("init_env");
		if (ft_strncmp(name, "_", ft_strlen(name)) == 0)
		{
			free(name);
			free(value);
		}
		else
			envadd_back(env, new_env(name, value));
		i++;
	}
}

void	init_env(t_env **env)
{
	extern char	**environ;

	if (!environ)
		fatal_error("init_env");
	*env = new_env(NULL, NULL);
	if (!*env)
		fatal_error("init_env");
	environ_to_env(environ, env);
	init_pwdenv(env);
}
