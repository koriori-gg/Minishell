/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:04:11 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ans;

	i = 0;
	if (!s || !f)
		return (NULL);
	ans = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ans)
		return (NULL);
	while (s[i] != '\0')
	{
		ans[i] = f(i, s[i]);
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

/*
char	test(unsigned int a, char b)
{
	return(a + b);
}

int	main(void)
{
	char	str[] = "ABC";

	printf("%s\n", ft_strmapi(str, test));
	return (0);
}
*/
