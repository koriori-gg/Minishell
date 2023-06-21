/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:32:39 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:32:39 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_env *env)
{
	env = env->next;
	while (env)
	{
		if (ft_strncmp(env->name, "_", ft_strlen(env->name)) && env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	printf("_=/usr/bin/env\n");
	return (0);
}
