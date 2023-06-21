/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:34:01 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:34:01 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_until_single_quote(char	**new_word, char *word)
{
	int	i;

	i = 1;
	while (word[i] != '\'')
		i += append_char(new_word, word[i]);
	i++;
	return (i);
}

static int	append_until_double_quote(char	**new_word, char *word)
{
	int	i;

	i = 1;
	while (word[i] != '\"')
		i += append_char(new_word, word[i]);
	i++;
	return (i);
}

void	remove_quote(t_token *token)
{
	int		i;
	char	*new_word;

	while (token)
	{
		if (token->kind != WORD || !token->word)
			return ;
		i = 0;
		new_word = NULL;
		while (token->word[i] != '\0')
		{
			if (token->word[i] == '\'')
				i += append_until_single_quote(&new_word, &token->word[i]);
			else if (token->word[i] == '\"')
				i += append_until_double_quote(&new_word, &token->word[i]);
			else
				i += append_char(&new_word, token->word[i]);
		}
		free(token->word);
		token->word = new_word;
		token = token->next;
	}
}
