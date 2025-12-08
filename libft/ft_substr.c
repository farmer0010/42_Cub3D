/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:05:00 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/21 10:07:59 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*str;
	size_t	i;

	str_len = 0;
	str = NULL;
	i = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (str_len < start)
		return (ft_strdup(""));
	if (start + len > str_len)
		len = str_len - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[start] && i < len)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
