/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:19 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:33:20 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_error(char *file, char *message)
{
	print_error("minishell: ");
	print_error("%s: %s\n", file, message);
}

void	command_error(char *file, char *message)
{
	print_error("minishell: ");
	if (!file)
		print_error(": %s\n", message);
	else
		print_error("%s: %s\n", file, message);
	exit(g_minishell.exit_status);
}

void	assert_error(char *message)
{
	print_error("minishell: ");
	print_error("assert error: %s\n", message);
	exit (255);
}

void	exit_error(char *arg, char *message)
{
	print_error("exit\n");
	print_error("minishell: exit: ");
	if (arg)
		print_error("%s: %s\n", arg, message);
	else
		print_error("%s\n", message);
}

void	usage_error(char *file, char *message)
{
	print_error("minishell: ");
	print_error("%s: usage: %s\n", file, message);
	exit(g_minishell.exit_status);
}
