/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:39 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/20 18:25:57 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_execute(char **environ, char **argv, char *path)
{
	free_double_pointer(environ);
	free_double_pointer(argv);
	free(path);
}

static void	ft_execve(char *path, char **argv, char **environ)
{
	if (execve(path, argv, environ) == -1)
	{
		if (errno == ENOEXEC)
			exit(0);
		else
			fatal_error("execute_child");
	}
}

static void	execute_child(t_env **env, t_node *node)
{
	char	*path;
	char	**argv;
	char	**environ;

	setup_pipe_child(node);
	do_redirect(node->redirect);
	argv = tokens_to_argv(node->command);
	if (!argv)
	{
		g_minishell.exit_status = 0;
		exit(0);
	}
	if (!validate_redirect(node))
		exit(1);
	if (is_builtin(node))
		exit(execute_builtin(env, node));
	environ = get_environ(*env);
	path = search_path(argv[0], environ);
	validate_path(environ, argv, path);
	ft_execve(path, argv, environ);
	free_execute(environ, argv, path);
	reset_redirect(node->redirect);
}

pid_t	execute_command(t_env **env, t_node *node)
{
	pid_t		pid;

	while (node)
	{
		setup_pipe(node);
		pid = fork();
		reset_sigactions();
		if (pid == -1)
			fatal_error("execute_command");
		else if (pid == 0)
			execute_child(env, node);
		set_sigactions();
		setup_pipe_parent(node);
		node = node->next;
	}
	return (pid);
}

int	wait_pipe(pid_t last_pid)
{
	pid_t	wait_result;
	int		wstatus;

	while (1)
	{
		g_minishell.signal = 0;
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			if (WIFSIGNALED(wstatus))
				g_minishell.exit_status = 128 + WTERMSIG(wstatus);
			else
				g_minishell.exit_status = WEXITSTATUS(wstatus);
		}
		if (wait_result == -1)
		{
			if (errno == EINTR)
				continue ;
			if (errno == ECHILD)
				break ;
			else
				fatal_error("execute_command");
		}
	}
	return (g_minishell.exit_status);
}
