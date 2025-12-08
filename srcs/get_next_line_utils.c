/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:23:57 by juyoukim          #+#    #+#             */
/*   Updated: 2025/05/16 10:43:19 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char) c)
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}

char	*get_line(char *str)
{
	char		*line;
	size_t		n;

	n = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[n] && str[n] != '\n')
		n++;
	line = (char *)malloc((n + 2));
	if (! line)
		return (NULL);
	n = 0;
	while (str[n] && str[n] != '\n')
	{
		line[n] = str[n];
		n++;
	}
	if (str[n] == '\n')
	{
		line[n] = str[n];
		n++;
	}
	line[n] = '\0';
	return (line);
}

char	*save_remain(char *str)
{
	char	*remain;
	size_t	i;
	size_t	j;

	if (! str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i++])
		return (free(str), NULL);
	j = 0;
	while (str[i + j])
		j++;
	remain = (char *)malloc(j + 1);
	if (! remain)
		return (NULL);
	j = 0;
	while (str[i])
		remain[j++] = str[i++];
	remain[j] = '\0';
	free(str);
	return (remain);
}
