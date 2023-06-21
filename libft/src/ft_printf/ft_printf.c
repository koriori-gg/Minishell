/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:01:54 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 11:47:24 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formats(va_list *ap, const char *format, int i)
{
	int	len;

	len = 0;
	if (format[i] == 'c')
		len += ft_putchar(va_arg(*ap, int));
	else if (format[i] == 's')
		len += ft_putstr(va_arg(*ap, char *));
	else if (format[i] == 'p')
	{
		len += write(1, "0x", 2);
		len += ft_putptr(va_arg(*ap, uintptr_t));
	}
	else if (format[i] == 'd' || format[i] == 'i')
		len += ft_putnbr(va_arg(*ap, int));
	else if (format[i] == 'u')
		len += ft_putuint(va_arg(*ap, unsigned int));
	else if (format[i] == 'x' || format[i] == 'X')
		len += ft_puthex(va_arg(*ap, unsigned int), format[i]);
	else if (format[i] == '%')
		len += ft_putchar(format[i]);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			len += ft_formats(&ap, format, i);
		}
		else
			len += ft_putchar(format[i]);
		i++;
	}
	if (len >= INT_MAX)
	{
		va_end(ap);
		return (-1);
	}
	va_end(ap);
	return (len);
}
/*
int	main(void)
{
	char te[100] = "3 Days Left";
	
	ft_printf("%c, %s, %p, %d, %i, %u, %x, %X, %%\n", 't', "42", te, 2, 3, 4, 5, 6);
	printf("%c, %s, %p, %d, %i, %u, %x, %X, %%\n", 't', "42", te, 2, 3, 4, 5, 6);
	
	system("leaks a.out");
	return (0);
}
*/