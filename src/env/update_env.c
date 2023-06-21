/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:10 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/21 12:19:04 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exists_env(t_env **env, char *arg)
{
	t_env	*head;
	size_t	len;
	size_t	arg_len;
	size_t	name_len;

	if (!*env)
		return (false);
	head = *env;
	head = head->next;
	while (head)
	{
		arg_len = ft_strlen(arg);
		name_len = ft_strlen(head->name);
		if (arg_len >= name_len)
			len = arg_len;
		else
			len = name_len;
		if (ft_memcmp(head->name, arg, len) == 0)
			return (true);
		head = head->next;
	}
	return (false);
}

static void	change_env_value(t_env **env, char *name, char *value)
{
	t_env	*head;

	head = *env;
	head = head->next;
	while (head)
	{
		if (ft_memcmp(head->name, name, ft_strlen(head->name)) == 0)
		{
			free(head->value);
			head->value = value;
			return ;
		}
		head = head->next;
	}
}

void	set_env(t_env **env, char *name, char *value)
{
	if (exists_env(env, name))
	{
		if (value)
			change_env_value(env, name, value);
		free(name);
	}
	else
		envadd_back(env, new_env(name, value));
}

void	update_env(t_env **env, char *arg)
{
	char	*name;
	char	*namelast;
	char	*value;

	namelast = ft_strchr(arg, '=');
	if (!namelast)
	{
		name = try_strdup(arg);
		value = NULL;
	}
	else
	{
		name = try_strndup(arg, namelast - arg);
		value = try_strdup(namelast + 1);
	}
	set_env(env, name, value);
}
