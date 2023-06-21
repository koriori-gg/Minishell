/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:01 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:35:01 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (!*lst)
		*lst = new;
	else
	{
		ptr = token_last(*lst);
		ptr->next = new;
	}
}

t_token	*new_token(char	*word, t_token_kind kind)
{
	t_token	*token;

	token = try_calloc(1, sizeof(t_token));
	token->word = word;
	token->kind = kind;
	token->next = NULL;
	return (token);
}

void	free_token(t_token *token)
{
	t_token	*cur;

	while (token)
	{
		cur = token;
		token = token->next;
		free(cur->word);
		free(cur);
	}
}
