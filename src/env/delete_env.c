/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:32:56 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:32:56 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(t_env **env, char *arg)
{
	t_env	*prev;
	t_env	*current;

	prev = *env;
	current = prev->next;
	while (current)
	{
		if (ft_memcmp(current->name, arg, ft_strlen(arg) + 1) == 0)
		{
			prev->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	delete_all_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	current = *env;
	next = current->next;
	while (current)
	{
		free(current->name);
		free(current->value);
		free(current);
		current = next;
		if (!next)
			break ;
		next = next->next;
	}
}
