/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:20:08 by nweber            #+#    #+#             */
/*   Updated: 2025/07/10 16:59:53 by nweber           ###   ########.fr       */
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

static char	*line_get(char *leftover)
{

}

static char	find_nextline(int fd, char *leftover)
{
	char	*buffer;
	size_t	b_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	b_read = 1;
	while (!ft_strchr(leftover, '\n') && b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(buffer);
			return (cleaner(&leftover));
		}
		buffer[b_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
		if (!leftover)
			break ;
	}
	free(buffer);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
}
