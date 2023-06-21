/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:02:01 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 11:47:24 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, strlen(s)));
}

int	ft_putptr(uintptr_t p)
{
	int	len;

	len = 0;
	if (p >= 16)
		len += ft_putptr(p / 16);
	len += write(1, &"0123456789abcdef"[p % 16], 1);
	return (len);
}

int	ft_putnbr(int i)
{
	int		len;
	char	*str;

	str = ft_itoa(i);
	len = ft_putstr(str);
	free(str);
	str = NULL;
	return (len);
}
