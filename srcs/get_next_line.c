/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:50:58 by juyoukim          #+#    #+#             */
/*   Updated: 2025/05/16 11:06:48 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_stack(int fd, char *stack)
{
	char	*buf;
	ssize_t	read_bytes;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while ((!stack || !gnl_strchr(stack, '\n')) && read_bytes > 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(buf);
			free_line(&stack);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		stack = gnl_strjoin(stack, buf);
	}
	free(buf);
	return (stack);
}

char	*get_next_line(int fd)
{
	static char	*stack;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	stack = read_stack(fd, stack);
	if (!stack)
		return (NULL);
	line = get_line(stack);
	stack = save_remain(stack);
	return (line);
}

char	*free_line(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}
