/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:03:37 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 12:02:20 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int			i;
	long int	num;
	char		c;
	char		m;

	i = 1;
	num = n;
	m = '-';
	if (n < 0)
	{
		num *= -1;
		write(fd, &m, 1);
	}
	while (n / 10 != 0)
	{
		n /= 10;
		i *= 10;
	}
	while (i > 0)
	{
		c = (num / i) + '0';
		write(fd, &c, 1);
		num -= (num / i) * i;
		i /= 10;
	}
}

/*
int	main(void)
{
	ft_putnbr_fd(-12345, 1);
	return (0);
}
*/
