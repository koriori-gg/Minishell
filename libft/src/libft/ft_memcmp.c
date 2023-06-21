/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:03:19 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t n)
{
	size_t			i;
	unsigned char	*ubuf1;
	unsigned char	*ubuf2;

	i = 0;
	if (!n)
		return (0);
	ubuf1 = (unsigned char *)buf1;
	ubuf2 = (unsigned char *)buf2;
	while (ubuf1[i] == ubuf2[i])
	{
		if (i == n - 1)
			break ;
		i++;
	}
	return (ubuf1[i] - ubuf2[i]);
}

/*
int	main(void)
{
	char	str1[] = "ABCD\0EFG";
	char	str2[] = "ABCD\0EFG";

	printf("%d\n", ft_memcmp(str1, str2, 9));
	printf("%d\n", memcmp(str1, str2, 9));
	return (0);
}
*/
