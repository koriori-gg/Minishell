/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:03:28 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*cstr;
	unsigned char	cc;

	i = 0;
	cstr = (unsigned char *)str;
	cc = (unsigned char)c;
	while (i < n)
	{
		cstr[i] = cc;
		i++;
	}
	return (str);
}

/*
int	main(void)
{
	char	str[] = "42Tokyo";

	ft_memset(str, '0', 2);
	printf("%s\n", str);
	return (0);
}
*/