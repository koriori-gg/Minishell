/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:34:06 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:34:07 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_same_operator(t_token *token, char *operator)
{
	if (token->kind != OPERATOR)
		return (false);
	return (ft_strncmp(token->word, operator, ft_strlen(token->word)) == 0);
}

bool	is_command(t_token *token)
{
	if (token->kind == END)
		return (false);
	if (ft_strncmp(token->word, "|", ft_strlen(token->word)) == 0)
		return (false);
	return (true);
}
