/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:34:10 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/20 11:33:08 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*node_last(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	node_add_back(t_node **lst, t_node *new)
{
	t_node	*ptr;

	if (!*lst)
		*lst = new;
	else
	{
		ptr = node_last(*lst);
		ptr->next = new;
	}
}

static void	init_redirect(t_node *node, char *word, t_node_kind kind)
{
	node->can_redirect = true;
	if (kind == REDIR_HEREDOC)
	{
		node->delimiter = try_calloc(1, sizeof(t_token));
		if (ft_strchr(word, '\'') || ft_strchr(word, '\"'))
			node->should_expand = false;
		else
			node->should_expand = true;
		node->delimiter->word = word;
		node->delimiter->kind = WORD;
		node->delimiter->next = NULL;
	}
	else if (kind == REDIR_OUT || kind == REDIR_IN || kind == REDIR_APPEND)
	{
		node->filename = try_calloc(1, sizeof(t_token));
		node->filename->word = word;
		node->filename->kind = WORD;
		node->filename->next = NULL;
		node->filefd = 0;
		if (kind == REDIR_OUT || kind == REDIR_APPEND)
			node->targetfd = STDOUT_FILENO;
		if (kind == REDIR_IN)
			node->targetfd = STDIN_FILENO;
		node->stashed_targetfd = 0;
	}
}

t_node	*new_node(char *word, t_node_kind kind)
{
	t_node	*node;

	node = try_calloc(1, sizeof(t_node));
	if (is_redirect(kind))
		init_redirect(node, word, kind);
	node->kind = kind;
	node->next = NULL;
	node->command = NULL;
	node->redirect = NULL;
	node->inpipe[READ] = STDIN_FILENO;
	node->inpipe[WRITE] = -1;
	node->outpipe[READ] = -1;
	node->outpipe[WRITE] = STDOUT_FILENO;
	return (node);
}
