/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:57 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/20 09:31:10 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_env *env, t_node *node)
{
	t_node	*redirect;

	while (node)
	{
		expand_variables(env, node);
		remove_quote(node->command);
		redirect = node->redirect;
		while (redirect)
		{
			if (redirect->kind == REDIR_OUT || redirect->kind == REDIR_IN
				|| redirect->kind == REDIR_APPEND)
				remove_quote(redirect->filename);
			else if (redirect->kind == REDIR_HEREDOC)
				remove_quote(redirect->delimiter);
			redirect = redirect->next;
		}
		node = node->next;
	}
}
