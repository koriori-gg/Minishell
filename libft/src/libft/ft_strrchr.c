/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:04:26 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;
	char	cc;

	len = ft_strlen(str);
	cc = (char)c;
	if (cc == '\0')
		return ((char *)&str[len]);
	while (len > 0)
	{
		if (str[len - 1] == cc)
			return ((char *)&str[len - 1]);
		len--;
	}
	return (NULL);
}

/*
int	main(void)
{
	char	str[] = "ABCABCDANSWER";
	int		c = 'A';
	printf("%s\n", ft_strrchr(str, c));
	return (0);
}
*/