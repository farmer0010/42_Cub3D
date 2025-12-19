/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:53:39 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/14 11:59:54 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		n;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s)+1));
	if (!res)
		return (NULL);
	n = 0;
	while (s[n])
	{
		res[n] = f(n, s[n]);
		n++;
	}
	res[n] = '\0';
	return (res);
}
