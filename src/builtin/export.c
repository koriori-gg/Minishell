/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:32:47 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/21 12:18:52 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	env = env->next;
	while (env)
	{
		if (ft_strncmp(env->name, "_", ft_strlen(env->name)))
		{
			if (env->value)
				printf("declare -x %s=\"%s\"\n", env->name, env->value);
			else
				printf("declare -x %s\n", env->name);
		}
		env = env->next;
	}
}

bool	should_append_env(char *arg)
{
	int		i;
	char	*equal;

	if (!is_alpha_under(arg[0]))
		return (false);
	i = 1;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!is_alpha_under_digit(arg[i]))
			return (false);
		i++;
	}
	equal = ft_strchr(arg, '=');
	return (equal - arg);
}

int	builtin_export(t_env **env, char **argv)
{
	int	i;
	int	status;

	status = 0;
	if (!argv[1])
		print_env(*env);
	else
	{
		i = 1;
		while (argv[i])
		{
			if (should_append_env(argv[i]))
				update_env(env, argv[i]);
			else
			{
				builtin_error("export", argv[i], "not a valid identifier");
				status = 1;
			}
			i++;
		}
	}
	return (status);
}
