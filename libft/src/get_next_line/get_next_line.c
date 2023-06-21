/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokuno <sokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 12:11:14 by sokuno            #+#    #+#             */
/*   Updated: 2023/01/10 15:24:03 by sokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*put_null_after_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static char	*get_new_save(char *save)
{
	size_t	i;
	char	*new_save;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0')
		return (put_null_after_free(&save));
	new_save = ft_strdup(&save[i + 1]);
	put_null_after_free(&save);
	return (new_save);
}

static char	*separate_line_from_save(char *save)
{
	size_t	i;
	char	*line;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] != '\0')
	{
		line[i] = save[i];
		if (save[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*read_file(int fd, char *save)
{
	char	*buff;
	char	*tmp;
	ssize_t	read_bytes;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!gnl_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (put_null_after_free(&buff));
		buff[read_bytes] = '\0';
		tmp = gnl_strjoin(save, buff);
		if (!tmp)
			return (put_null_after_free(&tmp));
		put_null_after_free(&save);
		save = tmp;
	}
	put_null_after_free(&buff);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_file(fd, save);
	if (!save || save[0] == '\0')
		return (put_null_after_free(&save));
	line = separate_line_from_save(save);
	if (!line)
		return (put_null_after_free(&save));
	save = get_new_save(save);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	system("leaks a.out");
	return (0);
}
*/