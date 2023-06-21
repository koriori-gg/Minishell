/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:32:35 by ihashimo          #+#    #+#             */
/*   Updated: 2023/06/06 13:32:36 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_option(char *str)
{
	if (!ft_strncmp(str, "-n\0", 3))
		return (true);
	else
		return (false);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	has_option;

	if (!argv[1])
		printf("\n");
	else
	{
		i = 1;
		has_option = is_option(argv[i]);
		if (has_option)
			i++;
		while (argv[i])
		{
			printf("%s", argv[i]);
			if (argv[i + 1])
				printf(" ");
			i++;
		}
		if (!has_option)
			printf("\n");
	}
	return (0);
}
