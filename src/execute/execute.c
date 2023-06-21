/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:41 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/20 17:54:59 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_env **env, t_node *node)
{
	pid_t		last_pid;
	t_node		*cur;
	bool		exist_redirect;

	cur = node;
	while (cur)
	{
		exist_redirect = true;
		if (open_redirect_file(*env, cur->redirect) < 0)
			exist_redirect = false;
		cur = cur->next;
	}
	if (!exist_redirect)
		return ;
	if (is_builtin(node) && !(node->next))
		execute_builtin(env, node);
	else
	{
		last_pid = execute_command(env, node);
		g_minishell.exit_status = wait_pipe(last_pid);
	}
}
