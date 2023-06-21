/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:08 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:35:08 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_token(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

char	**tokens_to_argv(t_token *token)
{
	int		i;
	char	**argv;
	int		token_count;

	if (!token)
		return (NULL);
	token_count = count_token(token);
	argv = try_calloc(token_count + 1, sizeof(char *));
	i = 0;
	if (!token->word && token_count == 1)
		return (argv);
	while (token)
	{
		if (token->kind == END)
			break ;
		if (token->word)
			argv[i] = try_strdup(token->word);
		else
			argv[i] = try_strdup("\0");
		i++;
		token = token->next;
	}
	return (argv);
}
