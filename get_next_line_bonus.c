/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:04:23 by nweber            #+#    #+#             */
/*   Updated: 2025/07/11 13:17:37 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	if (!*leftover || !**leftover)
		return (cleaner(leftover));
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
	if (!temp_leftover)
		return (free(line), NULL);
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
		return (cleaner(&leftover));
	b_read = 1;
	if (!leftover)
		leftover = ft_strdup("");
	if (!leftover)
		return (free(buffer), NULL);
	while (!ft_strchr(leftover, '\n') && b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == (ssize_t) - 1)
			return (free(buffer), cleaner(&leftover));
		buffer[b_read] = '\0';
		tmp = leftover;
		leftover = ft_strjoin(leftover, buffer);
		free(tmp);
		if (!leftover)
			break ;
	}
	return (free(buffer), leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	leftover[fd] = find_nextline(fd, leftover[fd]);
	if (!leftover[fd] || !*leftover[fd])
		return (cleaner(&leftover[fd]));
	line = get_line(&leftover[fd]);
	return (line);
}
