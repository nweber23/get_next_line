/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:20:08 by nweber            #+#    #+#             */
/*   Updated: 2025/07/10 18:35:26 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*cleaner(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

static char	*get_line(char **leftover)
{
	char	*line;
	char	*newline;
	char	*temp_leftover;
	size_t	len;

	if (!*leftover)
		return (NULL);
	newline = ft_strchr(*leftover, '\n');
	if (!newline)
	{
		line = ft_strdup(*leftover);
		cleaner(leftover);
		return (line);
	}
	len = (size_t)(newline - *leftover) + 1;
	line = ft_substr(*leftover, 0, len);
	if (!line)
		return (cleaner(leftover));
	temp_leftover = ft_strdup(*leftover + len);
	cleaner(leftover);
	*leftover = temp_leftover;
	return (line);
}

static char	*find_nextline(int fd, char *leftover)
{
	char	*buffer;
	ssize_t	b_read;
	char	*tmp;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	b_read = 1;
	if (!leftover)
		leftover = ft_strdup("");
	if (!leftover)
	{
		free(buffer);
		return (NULL);
	}
	while (!ft_strchr(leftover, '\n') && b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == (ssize_t) - 1)
		{
			free(buffer);
			free(leftover);
			return (NULL);
		}
		buffer[b_read] = '\0';
		tmp = leftover;
		leftover = ft_strjoin(leftover, buffer);
		free(tmp);
		if (!leftover)
			break ;
	}
	free(buffer);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = find_nextline(fd, leftover);
	if (!leftover || !*leftover)
		return (cleaner(&leftover));
	line = get_line(&leftover);
	return (line);
}
