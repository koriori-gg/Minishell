/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:43 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:33:43 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_pipe(int inpipe[2], int outpipe[2])
{
	inpipe[READ] = outpipe[READ];
	inpipe[WRITE] = outpipe[WRITE];
}

void	setup_pipe(t_node *node)
{
	if (!node->next)
		return ;
	if (pipe(node->outpipe) == -1)
		fatal_error("pipe");
	copy_pipe(node->next->inpipe, node->outpipe);
}

void	setup_pipe_child(t_node *node)
{
	if (node->outpipe[READ] >= 0 && close(node->outpipe[READ]) == -1)
		fatal_error("setup_pipe_child1");
	if (dup2(node->inpipe[READ], STDIN_FILENO) == -1)
		fatal_error("setup_pipe_child2");
	if (node->inpipe[READ] != STDIN_FILENO && close(node->inpipe[READ]) == -1)
		fatal_error("setup_pipe_child");
	if (dup2(node->outpipe[WRITE], STDOUT_FILENO) == -1)
		fatal_error("setup_pipe_child3");
	if (node->outpipe[WRITE] != STDOUT_FILENO
		&& close(node->outpipe[WRITE]) == -1)
		fatal_error("setup_pipe_child4");
}

void	setup_pipe_parent(t_node *node)
{
	if (node->inpipe[READ] != STDIN_FILENO)
		if (close(node->inpipe[READ]) == -1)
			fatal_error("setup_pipe_parent");
	if (node->next)
		if (close(node->outpipe[WRITE]) == -1)
			fatal_error("setup_pipe_parent");
}
