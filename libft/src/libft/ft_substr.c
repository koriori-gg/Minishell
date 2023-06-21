/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:04:32 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t n)
{
	size_t	i;
	size_t	len;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (start >= len || n <= 0)
		return (ft_strdup(""));
	if (len - start < n)
		n = len - start;
	p = (char *)malloc(sizeof(char) * (n + 1));
	if (!p)
		return (NULL);
	while (i < n && i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

/*
int	main(void)
{
	char	str[] = "42Tokyo";

	printf("%s\n", ft_substr(str, 3, 10));
	return(0);
}
*/
