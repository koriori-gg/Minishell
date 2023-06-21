/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:26:51 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/20 18:27:01 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	validate_redirect(t_node *node)
{
	t_node	*redirect;

	if (!node->redirect)
		return (true);
	redirect = node->redirect;
	while (redirect)
	{
		if (!node->redirect->can_redirect)
			return (false);
		redirect = redirect->next;
	}
	return (true);
}
