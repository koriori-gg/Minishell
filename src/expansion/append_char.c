/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:51 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:33:51 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_char(char **dest, char src)
{
	size_t	len;
	char	*new_word;

	len = 2;
	if (*dest)
		len += ft_strlen(*dest);
	new_word = try_calloc(len, sizeof(char));
	if (*dest)
		ft_strlcpy(new_word, *dest, len);
	new_word[len - 2] = src;
	new_word[len - 1] = '\0';
	free(*dest);
	*dest = new_word;
	return (1);
}
