/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:34:15 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:34:15 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*append_command(t_token *token, t_node *node)
{
	char	*word;

	word = try_strdup(token->word);
	token_add_back(&node->command, new_token(word, WORD));
	token = token->next;
	return (token);
}

static t_token	*append_redirect(t_token *token, t_node *node, t_node_kind kind)
{
	char	*word;

	word = try_strdup(token->next->word);
	if (!word)
		fatal_error("parse");
	node_add_back(&node->redirect, new_node(word, kind));
	token = token->next->next;
	return (token);
}

static t_token	*append_node(t_token *token, t_node *node, t_node **cur)
{
	node_add_back(&node, new_node(NULL, SIMPLE_CMD));
	*cur = (*cur)->next;
	token = token->next;
	return (token);
}

static void	init_node(t_node *node, t_token *token, bool *syntax_error)
{
	t_node	*cur;

	cur = node;
	while (token && token->kind != END)
	{
		if (token->kind == WORD)
			token = append_command(token, cur);
		else if (is_same_operator(token, ">") && token->next->kind == WORD)
			token = append_redirect(token, cur, REDIR_OUT);
		else if (is_same_operator(token, "<") && token->next->kind == WORD)
			token = append_redirect(token, cur, REDIR_IN);
		else if (is_same_operator(token, ">>") && token->next->kind == WORD)
			token = append_redirect(token, cur, REDIR_APPEND);
		else if (is_same_operator(token, "<<") && token->next->kind == WORD)
			token = append_redirect(token, cur, REDIR_HEREDOC);
		else if (is_same_operator(token, "|") && is_command(token->next))
			token = append_node(token, node, &cur);
		else
		{
			parser_error(token->word, syntax_error);
			return ;
		}
	}
}

t_node	*parse(t_token *token, bool *syntax_error)
{
	t_node	*node;

	if (is_same_operator(token, "|"))
	{
		parser_error(token->word, syntax_error);
		return (NULL);
	}
	node = new_node(NULL, SIMPLE_CMD);
	init_node(node, token, syntax_error);
	return (node);
}
