/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:04:29 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_first_count(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (ft_strchr(set, s1[i]) != 0)
		i++;
	if (s1[i] == '\0')
		return (0);
	return (i);
}

static size_t	check_last_count(char const *s1, char const *set)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(s1);
	while (ft_strchr(set, s1[n - 1 - i]) != 0)
		i++;
	return (n - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*p;
	size_t		fcount;
	size_t		lcount;

	if (!s1 || !set)
		return (NULL);
	fcount = check_first_count(s1, set);
	lcount = check_last_count(s1, set);
	p = ft_substr(s1, fcount, lcount - fcount);
	return (p);
}

/*
int	main(void)
{
	char	s1[] = "4234sota42Tokyo443";
	char	set[] = "43244";

	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}
*/
