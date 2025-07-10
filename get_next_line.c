/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:20:08 by nweber            #+#    #+#             */
/*   Updated: 2025/07/10 14:26:41 by nweber           ###   ########.fr       */
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

}

char	*get_next_line(int fd)
{
	static char	*leftover;

	if (fd  < 0|| BUFFER_SIZE <= 0)
		return (NULL);
}
