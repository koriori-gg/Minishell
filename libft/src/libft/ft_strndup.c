/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strndup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:24:06 by ihashimo          #+#    #+#             */
/*   Updated: 2023/04/11 09:24:07 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char		*dest;

	dest = (char *)ft_calloc(n + 1, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, (char *)src, n + 1);
	return (dest);
}
