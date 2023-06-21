/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:59 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:33:59 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_statuscode(char *str)
{
	return (str[0] == '$' && str[1] == '?');
}

bool	is_dollar_quote(char *str)
{
	return (str[0] == '$' && (str[1] == '\'' || str[1] == '\"'));
}

bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_under_digit(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}

bool	is_variable(char *str)
{
	if (!ft_strncmp(str, "$_", ft_strlen(str)))
		return (false);
	if (!ft_strncmp(str, "$_", 2) && !is_alpha_under_digit(str[2]))
		return (false);
	if (str[0] == '$' && is_alpha_under(str[1]))
		return (true);
	else
		return (false);
}
