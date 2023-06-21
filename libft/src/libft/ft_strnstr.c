/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:04:21 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (str2[0] == '\0')
		return ((char *)str1);
	while (i < n && str1[i] != '\0')
	{
		j = 0;
		while (i + j < n && str1[i + j] == str2[j])
		{
			if (str2[j + 1] == '\0')
				return ((char *)&str1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	char	str1[] = "AAABCDEFG";
	char	str2[] = "AABC";

	printf("%s\n", ft_strnstr(str1, str2, 10));
	printf("%s\n", strnstr(str1, str2, 10));
	return (0);
}
*/
