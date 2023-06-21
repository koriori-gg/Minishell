/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:03:16 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int ch, size_t n)
{
	size_t			i;
	unsigned char	*cbuf;
	unsigned char	cch;

	i = 0;
	cbuf = (unsigned char *)buf;
	cch = (unsigned char)ch;
	while (i < n)
	{
		if (cbuf[i] == cch)
			return (&cbuf[i]);
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	char	str[] = "ABCD\0EFG";

	printf("%s\n", (char *)ft_memchr(str, 'F', 10));
	return (0);
}	
*/
