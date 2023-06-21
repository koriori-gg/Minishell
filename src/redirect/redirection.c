/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:34:36 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/20 18:23:09 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_node_kind kind)
{
	if (kind == REDIR_IN)
		return (true);
	else if (kind == REDIR_OUT)
		return (true);
	else if (kind == REDIR_APPEND)
		return (true);
	else if (kind == REDIR_HEREDOC)
		return (true);
	else
		return (false);
}

static bool	has_redirect_error(t_node *redirect)
{
	if (g_minishell.should_heredoc_stop)
	{
		g_minishell.exit_status = ERROR;
		redirect->can_redirect = false;
		return (true);
	}
	else if (redirect->filefd < 0)
	{
		if (!is_heredoc(redirect->kind)
			&& exists_file(redirect->filename->word))
			file_error(redirect->filename->word, "Permission denied");
		else
			file_error(redirect->filename->word, "No such file or directory");
		redirect->filefd = open("/dev/null",
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		g_minishell.exit_status = ERROR;
		redirect->can_redirect = false;
		return (true);
	}
	return (false);
}

int	open_redirect_file(t_env *env, t_node *redirect)
{
	if (!redirect)
		return (0);
	if (redirect->kind == REDIR_OUT)
		redirect->filefd = open(redirect->filename->word,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirect->kind == REDIR_IN)
		redirect->filefd = open(redirect->filename->word, O_RDONLY);
	else if (redirect->kind == REDIR_APPEND)
		redirect->filefd = open(redirect->filename->word,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redirect->kind == REDIR_HEREDOC)
		redirect->filefd = read_heredoc(env, redirect);
	else
		assert_error("open_redirect_file");
	if (has_redirect_error(redirect))
	{
		free_redirect(redirect->next);
		redirect->next = NULL;
		return (-1);
	}
	return (open_redirect_file(env, redirect->next));
}

void	do_redirect(t_node *redirect)
{
	if (!redirect)
		return ;
	if (is_redirect(redirect->kind))
	{
		redirect->stashed_targetfd = stash_fd(redirect->targetfd);
		if (dup2(redirect->filefd, redirect->targetfd) == -1)
			fatal_error("do_redirect");
	}
	do_redirect(redirect->next);
}

void	reset_redirect(t_node *redirect)
{
	if (!redirect)
		return ;
	reset_redirect(redirect->next);
	if (is_redirect(redirect->kind))
	{
		if (close(redirect->filefd) == -1)
			fatal_error("reset_redirect1");
		if (close(redirect->targetfd) == -1)
			fatal_error("reset_redirect2");
		if (dup2(redirect->stashed_targetfd, redirect->targetfd) == -1)
			fatal_error("reset_redirect3");
	}
}
