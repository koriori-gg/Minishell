/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:04:03 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	len;

	len = ft_strlen(src);
	if (len + 1 < n)
	{
		ft_memcpy(dest, src, len + 1);
	}
	else if (n != 0)
	{
		ft_memcpy(dest, src, n - 1);
		dest[n - 1] = '\0';
	}
	return (len);
}

/*
int	main(void)
{
	char	dest[] = "ABCDE";
	char	src[] = "12345";

	printf("%lu\n", ft_strlcpy(dest, src, 3));
	printf("%s\n", dest);
	return (0);
}
*/