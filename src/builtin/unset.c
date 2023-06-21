/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:32:52 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:32:52 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_env **env, char **argv)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_alpha_under(argv[i][0]))
		{
			builtin_error("unset", argv[i], "not a valid identifier");
			status = 1;
		}
		else
			delete_env(env, argv[i]);
		i++;
	}
	return (status);
}
