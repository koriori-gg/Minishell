/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:34:08 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:34:09 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirect(t_node *redirect)
{
	t_node	*cur;

	while (redirect)
	{
		cur = redirect;
		redirect = redirect->next;
		if (is_redirect(cur->kind) && cur->kind == REDIR_HEREDOC)
			free_token(cur->delimiter);
		else if (is_redirect(cur->kind) && cur->kind != REDIR_HEREDOC)
			free_token(cur->filename);
		free(cur);
	}
}

void	free_node(t_node *node)
{
	t_node	*cur;

	while (node)
	{
		cur = node;
		node = node->next;
		free_token(cur->command);
		free_redirect(cur->redirect);
		free(cur);
	}
}
