/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:53 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/20 09:39:01 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_single_quote(char **new_word, char *word)
{
	int	i;

	append_char(new_word, word[0]);
	i = 1;
	while (word[i] != '\'')
	{
		if (word[i] == '\0')
			assert_error("Unclosed single quote");
		else
			i += append_char(new_word, word[i]);
	}
	i += append_char(new_word, word[i]);
	return (i);
}

int	expand_double_quote(t_env *env, char **new_word, char *word)
{
	int	i;

	append_char(new_word, word[0]);
	i = 1;
	while (word[i] != '\"')
	{
		if (word[i] == '\0')
			assert_error("Unclosed double quote");
		else if (is_variable(&word[i]))
			i += expand_variable(env, new_word, &word[i]);
		else if (is_statuscode(&word[i]))
			i += expand_statuscode(new_word);
		else if (i == 1 && is_dollar_quote(&word[i]))
			i += append_char(new_word, word[i]);
		else if (is_dollar_quote(&word[i]))
			i++;
		else
			i += append_char(new_word, word[i]);
	}
	i += append_char(new_word, word[i]);
	return (i);
}
