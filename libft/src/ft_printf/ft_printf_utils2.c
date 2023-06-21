/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:06:52 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 11:47:24 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	count_digit(long i)
{
	size_t	count;

	count = 0;
	if (i == 0)
		count = 1;
	while (i > 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

char	*ft_utoa(unsigned int n)
{
	char	*ans;
	long	ln;
	size_t	digit;

	ln = n;
	digit = count_digit(ln);
	ans = (char *)malloc((digit + 1) * sizeof(char));
	if (!ans)
		return (NULL);
	else if (ln == 0)
		ans[0] = '0';
	ans[digit] = '\0';
	while (ln > 0)
	{
		ans[digit - 1] = ln % 10 + '0';
		ln = ln / 10;
		digit--;
	}
	return (ans);
}

int	ft_putuint(unsigned int u)
{
	int		len;
	char	*str;

	str = ft_utoa(u);
	len = ft_putstr(str);
	free(str);
	str = NULL;
	return (len);
}

int	ft_puthex(unsigned int c, char format)
{
	int	len;

	len = 0;
	if (c >= 16)
		len += ft_puthex(c / 16, format);
	if (format == 'x')
		len += write(1, &"0123456789abcdef"[c % 16], 1);
	else if (format == 'X')
		len += write(1, &"0123456789ABCDEF"[c % 16], 1);
	return (len);
}
