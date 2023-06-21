/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:03:46 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 15:16:51 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	char	cc;

	i = 0;
	cc = (char)c;
	if (cc == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == cc)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	char	str[] = "42Tokyo";
	int		c = 'T';
	printf("%s\n", ft_strchr(str, c));
	return (0);
}
*/