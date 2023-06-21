/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_strdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:16 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:35:17 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*try_strdup(const char *str)
{
	char	*p;

	p = ft_strdup(str);
	if (!p)
		fatal_error("ft_strdup");
	return (p);
}
