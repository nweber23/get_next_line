/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:20:08 by nweber            #+#    #+#             */
/*   Updated: 2025/07/11 19:07:36 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(int fd, char *buffer, char *line, size_t *b_read)
{

}

static void	extract_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		ft_substr(line, 0, i + 1);
}

static void	buffer_clean(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		ft_memcpy(buffer, ft_strchr(buffer, '\n') + 1, ft_strlen(ft_strchr(buffer, '\n')));
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	size_t		b_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) == -1)
		return (ft_memcpy(buffer, '\0', 1), NULL);
	line = ft_strdup(buffer);
	if (!line)
		return (NULL);
	line = ft_read(fd, buffer, line, &b_read);
	if (!line)
		return (NULL);
	if (ft_strlen(line) == 0 || b_read == 0)
		return (free(line), NULL);
	extract_line(line);
	return (buffer_clean(buffer), line);
}
