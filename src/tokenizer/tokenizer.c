/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:05 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:35:06 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_operator(t_token **token, char *line)
{
	int		i;
	int		operator_len;
	char	*operator;
	char	**operators;

	operator = NULL;
	operators = init_operators();
	if (!operators)
		fatal_error("append_operator");
	i = 0;
	while (operators[i])
	{
		operator_len = ft_strlen(operators[i]);
		if (ft_strncmp(line, operators[i], operator_len) == 0)
		{
			operator = try_calloc(operator_len + 1, sizeof(char));
			ft_strlcpy(operator, &line[0], operator_len + 1);
			break ;
		}
		i++;
	}
	free(operators);
	token_add_back(token, new_token(operator, OPERATOR));
	return (operator_len);
}

int	count_to_single_quote(char *line, bool *syntax_error)
{
	int	i;

	i = 1;
	while (line[i] != '\'')
	{
		if (line[i] == '\0')
		{
			i += tokenizer_error
				("unclosed single quote", &line[i], syntax_error);
			return (i);
		}
		i++;
	}
	i++;
	return (i);
}

int	count_to_double_quote(char *line, bool *syntax_error)
{
	int	i;

	i = 1;
	while (line[i] != '\"')
	{
		if (line[i] == '\0')
		{
			i += tokenizer_error
				("unclosed double quote", &line[i], syntax_error);
			return (i);
		}
		i++;
	}
	i++;
	return (i);
}

int	append_word(t_token **token, char *line, bool *syntax_error)
{
	int		i;
	char	*word;

	i = 0;
	while (!is_brank(line[i]) && !is_metacharacter(line[i]) && line[i])
	{
		if (line[i] == '\'')
			i += count_to_single_quote(&line[i], syntax_error);
		else if (line[i] == '"')
			i += count_to_double_quote(&line[i], syntax_error);
		else
			i++;
	}
	word = try_calloc(i + 1, sizeof(char));
	ft_strlcpy(word, &line[0], i + 1);
	token_add_back(token, new_token(word, WORD));
	return (i);
}

t_token	*tokenize(char *line, bool *syntax_error)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	while (line[i] != '\0')
	{
		if (is_brank(line[i]))
			i++;
		else if (is_metacharacter(line[i]))
			i += append_operator(&token, &line[i]);
		else if (!is_metacharacter(line[i]))
			i += append_word(&token, &line[i], syntax_error);
		else
			i += tokenizer_error("unexpected token", &line[i], syntax_error);
	}
	token_add_back(&token, new_token(NULL, END));
	return (token);
}
