/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:34:32 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:34:32 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc(t_node_kind kind)
{
	if (kind == REDIR_HEREDOC)
		return (true);
	else
		return (false);
}

static bool	should_exit_heredoc(char *line, char *word)
{
	if (g_minishell.should_heredoc_stop
		|| !ft_strncmp(line, word, ft_strlen(word) + 1))
		return (1);
	else
		return (0);
}

int	read_heredoc(t_env *env, t_node *redirect)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) == -1)
		fatal_error("read_heredoc");
	g_minishell.should_heredoc_stop = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (should_exit_heredoc(line, redirect->delimiter->word))
		{
			free(line);
			break ;
		}
		if (redirect->should_expand)
			line = expand_heredoc(env, line);
		write(pfd[WRITE], line, ft_strlen(line));
		write(pfd[WRITE], "\n", 1);
		free(line);
	}
	if (close(pfd[WRITE]) == -1)
		fatal_error("read_heredoc");
	return (pfd[0]);
}
