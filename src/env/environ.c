/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:00 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:33:01 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_env_name(t_env *env)
{
	int	size;

	if (!env)
		return (0);
	size = 1;
	while (env->next)
	{
		size++;
		env = env->next;
	}
	return (size);
}

static size_t	count_env_value(t_env *env)
{
	size_t	size;

	size = 0;
	if (!env)
		return (0);
	while (env)
	{
		if (env->value)
			size++;
		env = env->next;
	}
	return (size);
}

static char	*join_env(t_env *env)
{
	size_t	len;
	char	*str;

	len = ft_strlen(env->name) + 2;
	if (env->value)
		len += ft_strlen(env->value);
	str = (char *)try_calloc(len, sizeof(char));
	ft_strlcpy(str, env->name, len);
	if (env->value)
	{
		ft_strlcat(str, "=", len);
		ft_strlcat(str, env->value, len);
	}
	return (str);
}

char	*get_env_value(t_env *env, char *name)
{
	char	*value;

	env = env->next;
	if (!name)
		return (NULL);
	while (env)
	{
		if (ft_memcmp(env->name, name, ft_strlen(env->name)) == 0)
		{
			if (!env->value)
				return (NULL);
			value = try_strdup(env->value);
			return (value);
		}
		env = env->next;
	}
	return (NULL);
}

char	**get_environ(t_env *env)
{
	char	**environ;
	size_t	size;
	size_t	i;
	t_env	*head;

	size = count_env_value(env);
	environ = (char **)try_calloc(size + 1, sizeof(char *));
	if (!environ)
		fatal_error("get_environ");
	i = 0;
	head = env->next;
	while (head)
	{
		if (head->value)
		{
			environ[i] = join_env(head);
			i++;
		}
		head = head->next;
	}
	environ[i] = NULL;
	return (environ);
}
