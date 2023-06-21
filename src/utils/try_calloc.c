/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_calloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:14 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:35:14 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*try_calloc(size_t count, size_t size)
{
	void	*p;

	p = ft_calloc(count, size);
	if (!p)
		fatal_error("calloc error");
	return (p);
}
