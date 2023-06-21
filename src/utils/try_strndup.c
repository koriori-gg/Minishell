/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_strndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:19 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:35:19 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*try_strndup(const char *src, size_t n)
{
	char	*p;

	p = ft_strndup(src, n);
	if (!p)
		fatal_error("ft_strndup");
	return (p);
}
