/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:17 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:33:17 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer_error(char *message, char *line, bool *syntax_error)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
		i++;
	print_error("minishell: ");
	print_error("syntax error: %s\n", message);
	*syntax_error = true;
	g_minishell.exit_status = TOKENIZE_ERROR;
	return (i);
}

void	fatal_error(char *message)
{
	print_error("minishell: ");
	print_error("fatal error: %s\n", message);
	exit(1);
}

void	builtin_error(char *command, char *arg, char *message)
{
	print_error("minishell: ");
	if (arg)
		print_error("%s: %s: %s\n", command, arg, message);
	else
		print_error("%s: %s\n", command, message);
}

void	standard_error(char *message)
{
	print_error("minishell: ");
	print_error("%s\n", message);
}

void	parser_error(char *word, bool *syntax_error)
{
	print_error("minishell: ");
	print_error("syntax error: near unexpected token %s\n", word);
	*syntax_error = true;
	g_minishell.exit_status = PARSE_ERROR;
}
