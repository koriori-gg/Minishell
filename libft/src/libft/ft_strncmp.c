/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:04:18 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*cstr1;
	unsigned char	*cstr2;

	i = 0;
	cstr1 = (unsigned char *)str1;
	cstr2 = (unsigned char *)str2;
	if (!n)
		return (0);
	while (cstr1[i] == cstr2[i])
	{
		if (i == n - 1 || str1[i] == '\0')
			break ;
		i++;
	}
	return (cstr1[i] - cstr2[i]);
}

/*
int	main(void)
{
	char	str1[] = "aaa";
	char	str2[] = "bbb";

	printf("%d\n", ft_strncmp(str1, str2, 3));
	return (0);
}
*/
