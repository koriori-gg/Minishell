/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:03:11 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digit(long int i)
{
	size_t	count;

	count = 0;
	if (i == 0)
		count = 1;
	else if (i < 0)
	{
		i *= -1;
		count++;
	}
	while (i > 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*ans;
	long int	ln;
	size_t		digit;

	ln = n;
	digit = count_digit(ln);
	ans = (char *)malloc((digit + 1) * sizeof(char));
	if (!ans)
		return (NULL);
	else if (ln == 0)
		ans[0] = '0';
	else if (ln < 0)
	{
		ans[0] = '-';
		ln *= -1;
	}
	ans[digit] = '\0';
	while (ln > 0)
	{
		ans[digit - 1] = ln % 10 + '0';
		ln = ln / 10;
		digit--;
	}
	return (ans);
}

/*
int	main(void)
{
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(2147483647));
	return (0);
}
*/
