/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:34:58 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:34:58 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_sigint(int signal)
{
	g_minishell.signal = signal;
}

int	display_new_line_if_needed(void)
{
	if (g_minishell.signal == SIGINT)
	{
		g_minishell.signal = 0;
		g_minishell.should_heredoc_stop = true;
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}

void	reset_sigactions(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &act, NULL) == -1)
		fatal_error("set_sigactions");
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		fatal_error("set_sigactions");
}

void	set_sigactions(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = set_sigint;
	if (isatty(STDIN_FILENO))
		rl_event_hook = display_new_line_if_needed;
	if (sigaction(SIGINT, &act, NULL) == -1)
		fatal_error("set_sigactions");
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		fatal_error("set_sigactions");
}
