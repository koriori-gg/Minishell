/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:55 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/21 11:51:39 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(t_env *env, char *line)
{
	int		i;
	char	*new_line;

	new_line = try_calloc(1, sizeof(char));
	i = 0;
	while (line[i] != '\0')
	{
		if (is_variable(&line[i]))
			i += expand_variable(env, &new_line, &line[i]);
		else if (is_statuscode(&line[i]))
			i += expand_statuscode(&new_line);
		else
			i += append_char(&new_line, line[i]);
	}
	free(line);
	return (new_line);
}

int	expand_variable(t_env *env, char **new_word, char *word)
{
	int		i;
	int		j;
	char	*name;
	char	*value;

	name = try_calloc(1, sizeof(char));
	i = 1;
	while (is_alpha_under_digit(word[i]))
		i += append_char(&name, word[i]);
	value = get_env_value(env, name);
	free(name);
	if (value)
	{
		j = 0;
		while (value[j])
			j += append_char(new_word, value[j]);
	}
	free(value);
	return (i);
}

int	expand_statuscode(char **new_word)
{
	int		i;
	char	*status;

	i = 0;
	status = ft_itoa(g_minishell.exit_status);
	if (!status)
		fatal_error("expand_statuscode");
	while (status[i] != '\0')
		i += append_char(new_word, status[i]);
	free(status);
	return (2);
}

void	expand_variable_token(t_env *env, t_token *token)
{
	int		i;
	char	*new_word;

	if (!token || !token->word || token->kind != WORD)
		return ;
	new_word = try_calloc(1, sizeof(char));
	i = 0;
	while (token->word[i] && !is_metacharacter(token->word[i]))
	{
		if (token->word[i] == '\'')
			i += expand_single_quote(&new_word, &token->word[i]);
		else if (token->word[i] == '\"')
			i += expand_double_quote(env, &new_word, &token->word[i]);
		else if (is_variable(&token->word[i]))
			i += expand_variable(env, &new_word, &token->word[i]);
		else if (is_statuscode(&token->word[i]))
			i += expand_statuscode(&new_word);
		else if (is_dollar_quote(&token->word[i]))
			i++;
		else
			i += append_char(&new_word, token->word[i]);
	}
	free(token->word);
	token->word = new_word;
	expand_variable_token(env, token->next);
}

void	expand_variables(t_env *env, t_node *node)
{
	if (!node)
		return ;
	expand_variable_token(env, node->command);
	if (node->redirect)
		expand_variable_token(env, node->redirect->filename);
}
