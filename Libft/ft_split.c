/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:42:34 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/17 15:45:19 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **str, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static int	ft_wlen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !(str[i] == c))
	{
		i++;
	}
	return (i);
}

static int	ft_wcnt(const char *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i])
		{
			cnt++;
			i += ft_wlen(&str[i], c);
		}
	}
	return (cnt);
}

static char	*ft_wcpy(char *str, int len)
{
	int			i;
	char		*cpy;

	i = 0;
	if (!str)
		return (NULL);
	cpy = (char *)malloc(len + 1);
	while (i < len)
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}	

char	**ft_split(char const *s, char c)
{
	char		**ch;
	int			i;
	int			size;
	size_t		n;

	i = 0;
	size = ft_wcnt(s, c);
	ch = (char **)malloc(sizeof(char *) * (size + 1));
	if (! ch)
		return (NULL);
	while (i < size)
	{
		while (*s && (*s == c))
			s++;
		n = ft_wlen((char *)s, c);
		ch[i] = ft_wcpy((char *)s, n);
		if (!ch[i])
		{
			return (ft_free(ch, i), NULL);
		}
		s += n;
		i++;
	}
	ch[i] = NULL;
	return (ch);
}
