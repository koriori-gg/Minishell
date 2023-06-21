/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:03:25 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t s)
{
	unsigned char	*cdest;
	unsigned char	*csrc;

	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (cdest < csrc)
		return (ft_memcpy(dest, src, s));
	while (s > 0)
	{
		cdest[s - 1] = csrc[s - 1];
		s--;
	}
	return (cdest);
}

/*
int	main(void)
{
	char	str1[] = "1234567";
	char	str2[] = "1234567";
	char	str3[] = "1234567";
	char	str4[] = "1234567";

	printf("%s\n", ft_memmove(str1 + 2, str1, 4));
	printf("%s\n", ft_memmove(str2, str2 + 2, 4));
	printf("%s\n", memmove(str3 + 2, str3, 4));
	printf("%s\n", memmove(str4, str4 + 2, 4));
	return (0);
}
*/