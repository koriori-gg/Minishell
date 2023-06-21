/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:03 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:35:03 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_operators(void)
{
	char	**operators;

	operators = try_calloc(7, sizeof(char *));
	operators[0] = ">>";
	operators[1] = "<<";
	operators[2] = ">";
	operators[3] = "<";
	operators[4] = "|";
	operators[5] = "\n";
	return (operators);
}

bool	is_operator(const char *s)
{
	size_t	i;
	char	**operators;

	operators = init_operators();
	if (!operators)
		fatal_error("is_operator");
	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(s, operators[i], ft_strlen(operators[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	is_brank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_metacharacter(char c)
{
	return (c && ft_strchr("|<> \t\n", c));
}
