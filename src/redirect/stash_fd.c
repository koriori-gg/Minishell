/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:34:38 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:34:39 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_fcntl(int old_fd)
{
	int			new_fd;
	struct stat	buf;

	new_fd = 10;
	while (fstat(new_fd, &buf) == 0)
		new_fd++;
	new_fd = dup2(old_fd, new_fd);
	if (new_fd == -1)
		fatal_error("ft_fctnl");
	return (new_fd);
}

int	stash_fd(int fd)
{
	int	stashfd;

	stashfd = ft_fcntl(fd);
	if (stashfd == -1)
		fatal_error("fcntl");
	if (close(fd) == -1)
		fatal_error("close");
	return (stashfd);
}
