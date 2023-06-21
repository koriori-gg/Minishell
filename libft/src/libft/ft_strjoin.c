/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:03:55 by sokuno            #+#    #+#             */
/*   Updated: 2023/03/30 14:07:28 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*ret;

	if (s1 == NULL && s2)
		s1 = "";
	else if (s1 && s2 == NULL)
		s2 = "";
	else if (s1 == NULL && s2 == NULL)
		return (NULL);
	ret = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	len = 0;
	i = 0;
	while (s1[i] != '\0')
		ret[len++] = s1[i++];
	j = 0;
	while (s2[j] != '\0')
		ret[len++] = s2[j++];
	ret[len] = '\0';
	return (ret);
}

/*
int	main(void)
{
	char	s1[] = "42";
	char	s2[] = "Tokyo";

	printf("%s\n", ft_strjoin(NULL, s2));
	return (0);
}
*/
