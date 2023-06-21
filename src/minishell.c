/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:21 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/21 12:27:34 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// __attribute__((destructor))
// void	destructor(void)
// {
// 	system("leaks -q minishell");
// }

t_minishell	g_minishell;

void	interpret(char *line, t_env *env)
{
	bool	syntax_error;
	t_token	*token;
	t_node	*node;

	syntax_error = false;
	token = tokenize(line, &syntax_error);
	free(line);
	if (syntax_error)
	{
		free_token(token);
		syntax_error = false;
		return ;
	}
	node = parse(token, &syntax_error);
	free_token(token);
	if (syntax_error)
	{
		free_node(node);
		syntax_error = false;
		return ;
	}
	expand(env, node);
	execute(&env, node);
	free_node(node);
}

int	main(void)
{
	char	*line;
	t_env	*env;

	g_minishell.exit_status = SUCCESS;
	init_env(&env);
	set_sigactions();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		interpret(line, env);
	}
	free_env(env);
	return (0);
}
