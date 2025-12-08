/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:01:55 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/18 11:19:19 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]))
	{
		if (end <= start)
			break ;
		end--;
	}
	res = (char *)malloc(end - start +1);
	if (start > end)
		return (ft_strdup(""));
	if (! res)
		return (NULL);
	ft_strlcpy(res, s1 + start, end - start + 1);
	return (res);
}
