/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:32:45 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/20 11:45:30 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	overflow(long num, const char *nptr, size_t i, int sign)
{
	long	n;

	n = nptr[i] - 48;
	if (sign == -1 && sign * num > (LONG_MAX - n) / 10)
		return (-1);
	if (sign == 1 && sign * num < (LONG_MIN + n) / 10)
		return (0);
	else
		return (1);
}

long	ft_atol(const char *nptr)
{
	size_t	i;
	long	sign;
	long	num;

	i = 0;
	num = 0;
	sign = -1;
	while (nptr[i] == ' ' || ('\t' <= nptr[i] && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		sign = sign * (44 - nptr[i]);
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		if (overflow(num, nptr, i, sign) != 1)
			return (overflow(num, nptr, i, sign));
		num = num * 10 - (nptr[i] - 48);
		i++;
	}
	return (sign * num);
}

int	is_numeric(char *str)
{
	int		i;
	int		sign;
	long	num;

	num = 0;
	sign = -1;
	if (!str)
		return (false);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		sign = sign * (44 - str[i++]);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		if (overflow(num, str, i, sign) != 1)
			return (false);
		num = num * 10 - (str[i] - 48);
		i++;
	}
	if (i == 0)
		return (false);
	return (true);
}

int	builtin_exit(char **argv)
{
	if (!argv[1])
		exit(0);
	if (argv[2])
	{
		if (is_numeric(argv[1]))
		{
			exit_error(NULL, "too many arguments");
			return (1);
		}
		else
		{
			exit_error(argv[1], "numeric argument required");
			exit(255);
		}
	}
	if (is_numeric(argv[1]))
	{
		printf("exit\n");
		exit(ft_atol(argv[1]) % 256);
	}
	else
	{
		exit_error(argv[1], "numeric argument required");
		exit(255);
	}
}
