/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:32:41 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:32:41 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_commands(void)
{
	char	**commands;

	commands = try_calloc(8, sizeof(char *));
	commands[0] = "echo";
	commands[1] = "cd";
	commands[2] = "pwd";
	commands[3] = "export";
	commands[4] = "unset";
	commands[5] = "env";
	commands[6] = "exit";
	return (commands);
}

bool	is_builtin(t_node *node)
{
	char	*command;
	char	**commands;
	int		i;

	if (!node || !node->command || !node->command->word)
		return (false);
	command = node->command->word;
	commands = init_commands();
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(command, commands[i], ft_strlen(command)) == 0)
		{
			free(commands);
			return (true);
		}
		i++;
	}
	free(commands);
	return (false);
}

int	execute_builtin(t_env **env, t_node *node)
{
	char	**argv;

	do_redirect(node->redirect);
	argv = tokens_to_argv(node->command);
	if (!ft_strncmp("echo", argv[0], ft_strlen(argv[0])))
		g_minishell.exit_status = builtin_echo(argv);
	else if (!ft_strncmp("pwd", argv[0], ft_strlen(argv[0])))
		g_minishell.exit_status = builtin_pwd();
	else if (!ft_strncmp("exit", argv[0], ft_strlen(argv[0])))
		g_minishell.exit_status = builtin_exit(argv);
	else if (!ft_strncmp("env", argv[0], ft_strlen(argv[0])))
		g_minishell.exit_status = builtin_env(*env);
	else if (!ft_strncmp("export", argv[0], ft_strlen(argv[0])))
		g_minishell.exit_status = builtin_export(env, argv);
	else if (!ft_strncmp("unset", argv[0], ft_strlen(argv[0])))
		g_minishell.exit_status = builtin_unset(env, argv);
	else if (!ft_strncmp("cd", argv[0], ft_strlen(argv[0])))
		g_minishell.exit_status = builtin_cd(env, argv);
	free_double_pointer(argv);
	reset_redirect(node->redirect);
	return (g_minishell.exit_status);
}
