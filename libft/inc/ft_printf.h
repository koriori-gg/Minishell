/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <maaacha.kuri05@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:01:48 by sokuno            #+#    #+#             */
/*   Updated: 2023/02/22 11:51:31 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
int		ft_putchar(int c);
int		ft_putstr(char *s);
int		ft_putptr(uintptr_t p);
int		ft_putnbr(int c);
size_t	count_digit(long i);
char	*ft_utoa(unsigned int n);
int		ft_putuint(unsigned int c);
int		ft_puthex(unsigned int c, char format);

#endif