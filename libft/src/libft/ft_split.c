/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:03:42 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	split_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	array_range(char const *s, char c)
{
	size_t	i;
	size_t	range;

	i = 0;
	range = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			range++;
			if (s[i + 1] == c || s[i + 1] == '\0')
				return (range);
		}
		i++;
	}
	return (range);
}

static char const	*check_first_split(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (s[0] == c)
	{
		while (s[i] == c)
			i++;
	}
	s += i;
	return (s);
}

static char	**error(char **ans)
{
	size_t	i;

	i = 0;
	while (ans[i] != NULL)
	{
		free(ans[i]);
		i++;
	}
	free(ans);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**ans;

	i = 0;
	if (!s)
		return (NULL);
	ans = (char **)malloc((split_count(s, c) + 1) * sizeof(char *));
	if (!ans)
		return (NULL);
	while (*s != '\0')
	{
		s = check_first_split(s, c);
		if (*s != '\0')
		{
			ans[i] = ft_substr(s, 0, array_range(s, c));
			if (!ans[i])
				return (error(ans));
			i++;
		}
		s += array_range(s, c);
	}
	ans[i] = NULL;
	return (ans);
}

/*
int	main(void)
{
	int 	i = 0;
	char	**ans;
	char	str[] = "004200To000kyo00";

	ans = ft_split(str, '0');
	while (ans[i] != NULL)
	{
		printf("%s\n", ans[i]);	
		i+
	}
	return (0);
}
*/