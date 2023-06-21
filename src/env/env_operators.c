/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:32:58 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:32:58 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *name, char *value)
{
	t_env	*ret;

	ret = try_calloc(1, sizeof(t_env));
	ret->name = name;
	ret->value = value;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

t_env	*envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	envadd_back(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (!*lst)
		*lst = new;
	else
	{
		ptr = envlast(*lst);
		ptr->next = new;
		new->prev = ptr;
	}
}

void	free_env(t_env *env)
{
	t_env	*cur;

	while (env)
	{
		cur = env;
		env = env->next;
		free(cur->name);
		free(cur->value);
		free(cur);
	}
}
