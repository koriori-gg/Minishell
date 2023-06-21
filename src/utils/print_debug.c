/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:11 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:35:11 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command(t_node *node)
{
	int		i;

	printf("==command==\n");
	i = 0;
	while (node)
	{
		printf("node[%d]: command\n", i);
		print_tokens(node->command);
		node = node->next;
		i++;
	}
}

void	print_redirects(t_node *redirect)
{
	t_node	*temp;

	temp = redirect;
	printf("====redirect====\n");
	if (!redirect)
		return ;
	while (temp)
	{
		if (temp->kind == REDIR_OUT || temp->kind == REDIR_IN
			|| temp->kind == REDIR_APPEND)
			printf("word = %s, kind = %d, targetfd = %d, next = %p\n",
				temp->filename->word, temp->kind, temp->targetfd, temp->next);
		else if (temp->kind == REDIR_HEREDOC)
			printf("word = %s, kind = %d, targetfd = %d, next = %p\n",
				temp->delimiter->word, temp->kind, temp->targetfd, temp->next);
		temp = temp->next;
	}
}

void	print_file_and_delimiter(t_node *node)
{
	int	i;

	printf("==filename==\n");
	i = 0;
	while (node)
	{
		printf("node[%d]: filename\n", i);
		print_redirects(node->redirect);
		node = node->next;
		i++;
	}
}

void	print_argv(char **argv)
{
	int	i;

	printf("==argv==\n");
	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		printf("argv[%d] = %s\n", i, argv[i]);
		i++;
	}
}

void	print_tokens(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		printf("word = %s, kind = %d, next = %p\n",
			temp->word, temp->kind, temp->next);
		temp = temp->next;
	}
}
